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

from openebtresos import OpenEb
from generate import Generate
from compile import Compile
from debug import Debug
from report import Report
from run import Run
from clean import Clean
from file_process import FileProcess

import xml.etree.ElementTree as ET

from common import Make_Dir

def Read_argument():
    # init parser
    parser = argparse.ArgumentParser(description="write args")
    # Options for tool
    parser.add_argument("-o", "--options", help="clean generate compile debug report", nargs='+', default=None)
    return parser.parse_args()

class mTest(): # chứa các biến đầu vào input
     # Lấy user config
    UserConfig_variable = "UserConfig.py"
    if os.path.exists(UserConfig_variable):
        exec(open(UserConfig_variable).read())
    
    PathGetvariableFromConfig = f'{PRO_DIR}/../env/env_{COMPILER}/env.py'
    if os.path.exists(PathGetvariableFromConfig):
        exec(open(PathGetvariableFromConfig).read())

    # get XDM_FILE in TS
    PathGetDirFromTS = f'{TEST_DIR}/{TEST_NAME}/{TEST_NAME}.py'
    if os.path.exists(PathGetDirFromTS):
        exec(open(PathGetDirFromTS).read())
    
    # get source files
    for SRC in SRC_DIRS:
        SRC_FILES += glob.glob(os.path.join(SRC,"*.c"))
        SRC_FILES += glob.glob(os.path.join(SRC,"*.s"))

    # Get path Coverity
    Tree = ET.parse('UserConfig.xml')
    Root = Tree.getroot()
    Coverity_Option = []
    Coverity_Enable = False
    Coverity_Enable = Root[0][0].text
    for Option_Coverity in Root[0][1]:
        Coverity_Option.append(Option_Coverity.text)

    def Parse_Config_Makefile(self,File_MakeFile, Split_Char):
        # Parsing all definitions in <TS>.mak file
        # Split_Char  "="
        try:
            MakeFile_Variables = {}
            MakeFile_Lines = FileProcess(File_MakeFile).Lines
            MultiLine_Value_Check = False
            Var_Name = ""
            Var_Value = ""
            for Line in MakeFile_Lines:
                # Bỏ qua comment line
                if Line.__contains__("#"):
                    continue

                if MultiLine_Value_Check:
                    # $(MODULE_PATH)/generic/include/Can.h \
                    if Line.endswith("\\"):
                        Var_Value = Var_Value + " " + Line.split("\\")[0].strip()
                        continue

                    Var_Value = Var_Value + " " + Line.strip()
                    if Var_Name not in MakeFile_Variables:
                        MakeFile_Variables[Var_Name] = Var_Value
                    else:
                        MakeFile_Variables[Var_Name] += " " + Var_Value

                    MultiLine_Value_Check = False

                # SRC_FILES += $(MODULE_PATH)/generic/src/Can.c
                elif Line.__contains__("+="):
                    Var_Name = "@" + Line.split("+=")[0].strip() + "@"
                    Var_Value = Line.split("+=")[1].strip()
                    # $(MODULE_PATH)/generic/include/Can.h \
                    if Var_Value.endswith("\\"):
                        Var_Value = Var_Value.split("\\")[0].strip()
                        MultiLine_Value_Check = True
                        continue

                    if Var_Name not in MakeFile_Variables:
                        MakeFile_Variables[Var_Name] = Var_Value
                        continue

                    MakeFile_Variables[Var_Name] += " " + Var_Value
                    
                # SRC_FILES = $(MODULE_PATH)/generic/include/Can.h
                elif Line.__contains__(Split_Char):
                    Var_Name = "@" + Line.split(Split_Char)[0].strip() + "@" \
                        if Split_Char == "=" else Line.split(Split_Char)[0].strip()
                    Var_Value = Line.split(Split_Char, 1)[1].strip()
                    if Var_Value.endswith("\\"):
                        Var_Value = Var_Value.split("\\")[0].strip()
                        MultiLine_Value_Check = True
                        continue

                    if Var_Name not in MakeFile_Variables:
                        MakeFile_Variables[Var_Name] = Var_Value
                    else:
                        MakeFile_Variables[Var_Name] += " " + Var_Value
        except Exception as ex:
            raise ex

        return MakeFile_Variables


class mRunTool():
    def __init__(self, step):
        self.Step = step
        self.Mytest = mTest()
        print("")
        logging.info("Initial SUCCEEDED")
        print("")

    def Start(self):
        if self.Step == "eb":
            OpenEb(mTest=self.Mytest).Run()
        elif self.Step == "generate":
            Generate(mTest=self.Mytest).Run()
        elif self.Step == "compile":
            Compile(mTest=self.Mytest).Run()
        elif self.Step == "debug":
            Debug(mTest=self.Mytest, Debug = 1).Run()
        elif self.Step == "nodebug":
            Debug(mTest=self.Mytest, Debug = 2).Run()
        elif self.Step == "report":
            Report(mTest=self.Mytest).Run()
        elif self.Step == "run":
            Run(mTest=self.Mytest).Run()
        elif self.Step == "clean":
            Clean(mTest=self.Mytest).Run()
        else:
            print("Check steps again, please !")

if __name__ == '__main__':
    Argument = Read_argument()
    logging.info("options = %s ",Argument.options[0])
    RunNew = mRunTool(Argument.options[0])
    RunNew.Start()