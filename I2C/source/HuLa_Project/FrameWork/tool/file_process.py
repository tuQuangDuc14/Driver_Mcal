import os
from os.path import isfile, dirname, exists
from typing import List
import cchardet as chardet

import logging
logger = logging.getLogger(__name__)
logging.basicConfig(
    level=logging.DEBUG,
    handlers=[logging.StreamHandler()],
    datefmt='%Y-%m-%d %H:%M:%S',
    format='[%(asctime)s %(levelname)s] --> %(module)s: %(message)s'
)

class FileProcess:
    def __init__(self, Path: str, Encode: str = 'utf-8'):
        self.Path = Path
        self.Encode = Encode
        self.Content = ''

    def Get_Path(self):
        return self.Path
    
    def Set_Path(self, Path_Str: str):
        self.Path = Path_Str
        self.Content = ''

    @property
    def Get_Content(self):
        return self.Read_File()

    @property
    def Lines(self):
        # Read all lines of file's content
        return self.Read_File().splitlines()

    def Read_File(self):
        if not self.Content:
            if not isfile(self.Get_Path()):
                logger.error(f"File does not exist: {self.Get_Path()} ")

            with open(self.Get_Path(), 'rb') as Reader:
                Content_Bytes = Reader.read()

            try:
                self.Content = Content_Bytes.decode(self.Encode)
            except Exception as ex:
                detect_Encoding = chardet.detect(Content_Bytes)["encoding"]
                self.Content = Content_Bytes.decode(detect_Encoding)

            self.Content = '\n'.join(self.Content.splitlines())

        return self.Content

    def Write_File(self, Content: List[str], Mode: str = 'w'):
        if not exists(dirname(self.Get_Path())):
            os.makedirs(dirname(self.Get_Path()))

        if Mode == 'a':
            self.Read_File()

        with open(self.Get_Path(), Mode, encoding=self.Encode) as F_obj:
            F_obj.write(Content)
            if Mode == 'w':
                self.Content = Content

        return self.Content
