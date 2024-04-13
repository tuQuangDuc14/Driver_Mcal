# lib parser
import argparse
# lib logging
import logging
logger = logging.getLogger(__name__)
logging.basicConfig(
    level=logging.DEBUG,
    handlers=[logging.StreamHandler()],
    datefmt='%Y-%m-%d %H:%M:%S',
    format='[%(asctime)s %(levelname)s] --> %(module)s: %(message)s'
)

import os
import glob
import shutil
import yaml
import re

from openebtresos import OpenEb
from generate import Generate
from file_process import FileProcess

from common import CommonStep,Make_Dir,StepStatus

def Read_argument():
    # init parser
    parser = argparse.ArgumentParser(description="write args")
    # Options for tool
    parser.add_argument("-o", "--options", help="clean generate compile debug report", nargs='+', default=None)
    return parser.parse_args()

class Compile(CommonStep):
    def __init__(self, mTest):
        self.Step = "compile"
        super().__init__(self.Step, mTest.TEST_NAME)
        self.mTest = mTest
        # create folder compile
        self.CompileDir = os.path.join(os.path.normpath(self.mTest.OUTPUT_DIR), "compile")
        Make_Dir(self.CompileDir)
        # create folder result
        Temp = os.path.join(self.CompileDir, "result")
        if not os.path.isdir(Temp):
            Make_Dir(Temp)
        self.ResultFile = os.path.join(Temp, "result.log")

        # Tạo path file Elf, bin, map  
        self.mTest.ELF_FILE =  f'{self.mTest.OUTPUT_DIR}/compile/{self.mTest.TEST_NAME}.elf'
        self.mTest.BIN_FILE =  f'{self.mTest.OUTPUT_DIR}/compile/{self.mTest.TEST_NAME}.bin'
        self.mTest.HEX_FILE =  f'{self.mTest.OUTPUT_DIR}/compile/{self.mTest.TEST_NAME}.hex'
        self.mTest.MAP_FILE =  os.path.normpath(f'{self.mTest.OUTPUT_DIR}/compile/{self.mTest.TEST_NAME}.map')

        # path folder generate
        self.GenDir = os.path.join(os.path.normpath(self.mTest.OUTPUT_DIR), "generate", mTest.GENERATOR)

        # Parse Config in MakeFile 
        self.MyMakeFile_Config = {}
        self.MyMakeFile_Config.update(self.mTest.Parse_Config_Makefile(f'{self.mTest.TEST_DIR}/{self.mTest.TEST_NAME}/{self.mTest.TEST_NAME}.mak',"="))

    # Remove and create folder or file 
    def Create_Dir_Or_File(self,Path):
        if os.path.exists(Path):
            shutil.rmtree(Path)
        Make_Dir(Path)

    # Bước 1: Parse RegEx Yaml file 
    def Parsing_RegEx_Yaml(self):
        RegEx_File = os.path.join(os.path.dirname(__file__), "RegEx.yaml")
        with open(RegEx_File, "r", encoding="utf8") as File:
            Arr_RegEx = yaml.load(File, Loader=yaml.FullLoader)
        return Arr_RegEx
    # Bước 2: Remove tất cả các vùng không cần thiết trong source code 
    def Remove_Unnecessary_Areas(self, File_Content, Arr_RegEx):
        try:
            Matches = re.findall(Arr_RegEx["REMOVAL_AREA"], File_Content, re.DOTALL | re.MULTILINE)
            for Match in Matches:
                File_Content = File_Content.replace(Match, "")
        except Exception as ex:
            raise ex
        return File_Content
    # Bước 3: Thực hiện tất cả conditions ở trong source code 
    def Handle_Conditions(self, File_Content,Arr_RegEx):
        try:
            Matches = re.findall(Arr_RegEx["CONDITION_AREA"],File_Content, re.I | re.DOTALL | re.MULTILINE)
            for Match in Matches:
                Condition_Area = Match[0]
                Condition_Checking = Match[1]
                if len(Condition_Checking.split("==")) < 2:
                    continue

                First_Clause = Condition_Checking.split("==")[0] # @M4_FLATFORM_STM32@
                Second_Clause = Condition_Checking.split("==")[1] # 1

                if self.MyMakeFile_Config[First_Clause] != Second_Clause:
                    File_Content = File_Content.replace(Condition_Area, "")

            # Remove conditions
            for Block_Sign in [Arr_RegEx["START_CONDITION"],Arr_RegEx["END_CONDITION"]]:
                File_Content = re.sub(Block_Sign, "", File_Content)
                
        except Exception as ex:
            raise ex

        return File_Content

    def Run(self):
        self.Result = StepStatus.FAILED
        self.LetStart()

        # Lấy SRC_FILES và INCLUDE_DIRS của Eb tresos gen ra và tạo folder
        SRC_FILES_TEMP = self.mTest.SRC_FILES + glob.glob(os.path.join(self.GenDir, "src", "*.c"))
        INCLUDE_DIRS_TEMP = self.mTest.INCLUDE_DIRS + [os.path.join(self.GenDir, "include")]
        INCLUDE_FILES = []
        for FILES in INCLUDE_DIRS_TEMP:
            INCLUDE_FILES = INCLUDE_FILES + glob.glob(os.path.join(FILES, "*.h"))

        FOLDER_SOURCE_OUTPUT = f'{self.mTest.PRO_DIR}/../output/{self.mTest.MODULE}/{self.mTest.TEST_NAME}/src'
        FOLDER_INCLUDE_OUTPUT = f'{self.mTest.PRO_DIR}/../output/{self.mTest.MODULE}/{self.mTest.TEST_NAME}/include'
        self.Create_Dir_Or_File(FOLDER_INCLUDE_OUTPUT)
        self.Create_Dir_Or_File(FOLDER_SOURCE_OUTPUT)

        # Copy to folder and Remove variable M4 
        Arr_RegEx = self.Parsing_RegEx_Yaml()
        for SRC in SRC_FILES_TEMP:
            Name_File = os.path.basename(SRC)
            shutil.copyfile(SRC,f'{FOLDER_SOURCE_OUTPUT}/{Name_File}')
            # Remove M4
            My_File = FileProcess(f'{FOLDER_SOURCE_OUTPUT}/{Name_File}')
            My_File.Read_File()
            File_Content = My_File.Content
            File_Content = self.Handle_Conditions(File_Content,Arr_RegEx)
            My_File.Write_File(File_Content)
        for INCLUDE in INCLUDE_FILES:
            Name_File = os.path.basename(INCLUDE)
            shutil.copyfile(INCLUDE,f'{FOLDER_INCLUDE_OUTPUT}/{Name_File}')
            # Remove M4
            My_File = FileProcess(f'{FOLDER_INCLUDE_OUTPUT}/{Name_File}')
            My_File.Read_File()
            File_Content = My_File.Content
            File_Content = self.Handle_Conditions(File_Content,Arr_RegEx)
            My_File.Write_File(File_Content)
        
        SRC_FILES = []
        SRC_FILES = SRC_FILES + glob.glob(os.path.join(FOLDER_SOURCE_OUTPUT, "*.c"))
        SRC_FILES = SRC_FILES + glob.glob(os.path.join(FOLDER_SOURCE_OUTPUT, "*.s"))
        INCLUDE_DIRS = []
        INCLUDE_DIRS.append(FOLDER_INCLUDE_OUTPUT) 


        # Lấy linker Option
        LinkerOption = [opt.replace("MAP_FILE_REPLACE", self.mTest.MAP_FILE) for opt in self.mTest.LK_OPTS]
        ListCommands = []
       
        for SRC_FILE in SRC_FILES:
            # Chuyển file .c thành .o
            SRC_FILE = os.path.normpath(SRC_FILE)   # ví dụ  C://  -> C:/
            logging.info(f"File compile : {SRC_FILE}")
            Filename = os.path.basename(SRC_FILE) # Lấy tên của file
            Filename = f'{Filename[:-1]}o' # gpio.c -> gpio.o
            OutFile = os.path.join(self.CompileDir, Filename)
            LinkerOption += [OutFile]      # Thêm file .o vào linker option

            Opts = []
            if SRC_FILE[-2:] == ".c":
                for opt in self.mTest.CC_OPTS:
                    Opts += [opt]
                Opts += ["-c", SRC_FILE]
                for INCLUDE_DIR in INCLUDE_DIRS:
                    INCLUDE_DIR = os.path.normpath(INCLUDE_DIR)
                    Opts += [f'-I{INCLUDE_DIR}']
                Opts += ['-o', OutFile]
                Command = CommonStep.Sum_Command(self.mTest.CC_FILE,Opts, self.mTest.Coverity_Enable, self.mTest.Coverity_Option)
                ListCommands.append(Command)
            elif SRC_FILE[-2:] == ".s":
                for opt in self.mTest.AC_OPTS:
                    Opts += [opt]
                Opts += [SRC_FILE]
                Opts += ["-o", OutFile]
                Command = CommonStep.Sum_Command(self.mTest.AC_FILE,Opts, self.mTest.Coverity_Enable, self.mTest.Coverity_Option)
                ListCommands.append(Command)

        # Execute cái ListCommands trên
        for Cmd in ListCommands:
            Result, AllLog = CommonStep.RunCmd(Cmd, Shell = True)
        
        if Result:
            LinkerOption += ["-o"]
            LinkerOption += [f'{os.path.join(self.CompileDir, self.mTest.TEST_NAME)}.elf']
            Command = CommonStep.Sum_Command(self.mTest.LK_FILE,LinkerOption, self.mTest.Coverity_Enable, self.mTest.Coverity_Option)
            Result, AllLog = CommonStep.RunCmd(Command, Shell = True)
            if self.mTest.COMPILER != "ghs":
                if Result:
                    # BIN_FILE
                    Options = []
                    Options += self.mTest.BIN_COMPILE_OPTS
                    Options.append(self.mTest.ELF_FILE)
                    Options.append(self.mTest.BIN_FILE)
                    Command = CommonStep.Sum_Command(os.path.normpath(self.mTest.POST_COMPILE),Options, self.mTest.Coverity_Enable, self.mTest.Coverity_Option)
                    Result, AllLog = CommonStep.RunCmd(Command, Shell = True)

                    # HEX_FILE
                    Options = []
                    Options += self.mTest.HEX_COMPILE_OPTS
                    Options.append(self.mTest.ELF_FILE)
                    Options.append(self.mTest.HEX_FILE)
                    Command = CommonStep.Sum_Command(os.path.normpath(self.mTest.POST_COMPILE),Options, self.mTest.Coverity_Enable, self.mTest.Coverity_Option)
                    Result, AllLog = CommonStep.RunCmd(Command, Shell = True)

        with open(self.ResultFile, "w+") as file:
            if Result is False:
                self.Result = StepStatus.FAILED
                file.write("0")
            else:
                self.Result = StepStatus.SUCCEEDED
                file.write("1")

        self.LetEnd()

