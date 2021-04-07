import serial
import threading
import time
import os
import re
import fileinput
# from glob import glob
# import subprocess as sp

import datetime
print(datetime.date.today())


# import xlsxwriter
# import xlrd


print('Hellow World:',time.time()) #时间戳：秒

datetime.datetime.today()
datetime.datetime.now().date()

time_now=datetime.datetime.now()

print(time_now.hour)

print(time_now.minute)

TheTimeIs=time.ctime()


""" # /////////////////////////////////////
# >>> datetime.datetime.today()  # 获取当前时间

# datetime.datetime(2017, 1, 25, 17, 47, 47, 523000)

# >>> datetime.datetime.now().day  # 获取当天日期

# 25

# >>> datetime.datetime.now().year  # 获取当前年份

# 2017

# >>> datetime.datetime.now().date()  # 返回date类型

# time_now=datetime.datetime.now()

# print(time_now.hour)

# print(time_now.minute)
# //////////////////////////////////// """

# #//////////////////////////////////////////////////////////////////////////////调用powershell的类
# class PowerShell:
#     # from scapy
#     def __init__(self, coding, ):
#         cmd = [self._where('PowerShell.exe'),
#                "-NoLogo", "-NonInteractive",  # Do not print headers
#                "-Command", "-"]  # Listen commands from stdin
#         startupinfo = sp.STARTUPINFO()
#         startupinfo.dwFlags |= sp.STARTF_USESHOWWINDOW
#         self.popen = sp.Popen(cmd, stdout=sp.PIPE, stdin=sp.PIPE, stderr=sp.STDOUT, startupinfo=startupinfo)
#         self.coding = coding

#     def __enter__(self):
#         return self

#     def __exit__(self, a, b, c):
#         self.popen.kill()

#     def run(self, cmd, timeout=6):                                         #timeout=0  延时
#         b_cmd = cmd.encode(encoding=self.coding)
#         try:
#             b_outs, errs = self.popen.communicate(b_cmd, timeout=timeout)
#         except sp.TimeoutExpired:
#             self.popen.kill()
#             b_outs, errs = self.popen.communicate()
#         outs = b_outs.decode(encoding=self.coding)
#         return outs, errs

#     @staticmethod
#     def _where(filename, dirs=None, env="PATH"):
#         """Find file in current dir, in deep_lookup cache or in system path"""
#         if dirs is None:
#             dirs = []
#         if not isinstance(dirs, list):
#             dirs = [dirs]
#         if glob(filename):
#             return filename
#         paths = [os.curdir] + os.environ[env].split(os.path.pathsep) + dirs
#         try:
#             return next(os.path.normpath(match)
#                         for path in paths
#                         for match in glob(os.path.join(path, filename))
#                         if match)
#         except (StopIteration, RuntimeError):
#             raise IOError("File not found: %s" % filename)
#//////////////////////////////////////////////////////////////////////////


#/////////////////////////////////////////////////////////////////////////文本处理
# pscmd='Add-Type -AssemblyName System.speech;\
#             $speak = New-Object System.Speech.Synthesis.SpeechSynthesizer;\
#             $speak.Rate = 0;\
#             $speak.Speak("天猫精灵")'               #powershell文本朗读指令
# cmd="天猫精灵"
# cend='end'  #语料结束标志
# corpus_n=1
# StandardCmd_n=''
# Number_n=0
# SuccessNum_n=0
# FailDispaly_n=[]
# Corpus=[]
# StandardCmd=[]
# Number=[]
# SuccessNum=["成功次数"]
# FailDispaly=["失败案例"]




# def changepscmd():                           #改变朗读语句
#     global pscmd 
#     global cmd   
#     global corpus_n
#     global StandardCmd_n
#     global Number_n
#     global FailDispaly_n
#     global SuccessNum_n
#     global Corpus
#     global StandardCmd
#     global Number
#     global SuccessNum
#     global FailDispaly
    
#     with PowerShell('GBK') as ps:    
#         ps.run(pscmd)
#         print("天猫精灵") 
        
#     with open('LogSpeech.txt', mode='a',encoding='utf-8') as LogSpeech:
#         LogSpeech.writelines([time.ctime(), '  say :',"天猫精灵",'\n'])
#         LogSpeech.close()

#     data = xlrd.open_workbook('test.xlsx')#打开表格
#     mycmd=data.sheet_by_index(0)

#     Corpus=mycmd.col_values(0)
#     StandardCmd=mycmd.col_values(1)
#     Number=mycmd.col_values(2)
#     # worksheet.write_column('A1',mycmd.col_values(0))
#     # worksheet.write_column('B1',mycmd.col_values(0))

#     fcmd=mycmd.cell_value(corpus_n,0)
#     scmd=mycmd.cell_value(corpus_n,1)
#     if Number_n==0:
#         Number_n=mycmd.cell_value(corpus_n,2)

#     Number_n-=1

#     if Number_n==0:
#         disp=",".join(FailDispaly_n)
#         SuccessNum.append(SuccessNum_n)
#         FailDispaly.append(disp)
#         corpus_n+=1
#         FailDispaly_n=[]
#         SuccessNum_n=0
        

  
#     StandardCmd_n=str(scmd)
#     cmd=str(fcmd)

    
#     #print(cmd)   
#     pscmd0=pscmd
#     p = re.compile("天猫精灵")
#     pscmd1 = p.sub(cmd,pscmd0)

#     return pscmd1 

# def checkcmd(log):
#     global SuccessNum_n
#     global FailDispaly_n
#     p = re.compile(", ")
#     pscmd1 = p.sub('',log)
#     if pscmd1.find(StandardCmd_n)>=0:
#         SuccessNum_n+=1
#     else:
#         if len(FailDispaly_n)<10:
#             FailDispaly_n.append(log)



#//////////////////////////////////////////////////////////////////////////////////保存数据线程入口
# def SaveExcel():
#     while True:
#         time.sleep(5)
#         workbook = xlsxwriter.Workbook('TestResult.xlsx')    # 新建excel表
#         worksheet = workbook.add_worksheet('sheet1')    # 新建sheet（sheet的名称为"sheet1"）
#         #headings = ["天猫语料","标准指令","x秒接收指令","判断"]    # 设置表头
#         worksheet.write_column('A1',Corpus)
#         worksheet.write_column('B1',StandardCmd)
#         worksheet.write_column('C1',Number)
#         worksheet.write_column('D1',SuccessNum)
#         worksheet.write_column('E1',FailDispaly)

#         workbook.close() 
        


#//////////////////////////////////////////////////////////////////////////////////朗读线程函数入口
# def Speech():
#     while True:                                   
#         with PowerShell('GBK') as ps:
            
#             pscmd1=changepscmd()
#             outs, errs = ps.run(pscmd1)              #在run函数中输入powershell指令  time.sleep(2)
#             print('error:', os.linesep, errs)
#             print('output:', os.linesep, outs)
#         with open('LogSpeech.txt', mode='a',encoding='utf-8') as LogSpeech:
#             LogSpeech.writelines([time.ctime(), '  say :',cmd,'\n'])
#             LogSpeech.close()
#         print(cmd)#打印朗读的语料
        
#         time.sleep(8)

#         if cend==cmd:
#             print('-------------end--------------')
#             break


#/////////////////////////////////////////////////////////////////////////////////////串口调试
ser = serial.Serial()

print("请输入正确的串口号按回车健运行：")
MycomX='COM'+str(input())

ser.port =MycomX # 串口
print(ser.name)


ser.baudrate = 115200  #波特率
ser.bytesize = 8
ser.parity = serial.PARITY_NONE
ser.stopbits = 1
ser.open() # 开启串口

# #///////////////////////////////////////////////////////////////////////////////////主线程串口接收
def UartData():
    while True:

        #ch = ser.read() # 收一个bytes
        ch=ser.readline()#读取以“\n”结尾的行
        print(ch)
        log=ch.decode(encoding='utf-8')
            # cmdl=len(log)                   #
            # itlog=log.find('send')
            # if itlog==0&cmdl>86:                    #
            #     print(itlog)
            #     print('\n',len(log),'\n')
            #     slog=log[(itlog+5):]
            #     print('log is---------> %s' % slog)
            #     checkcmd(slog)
        with open('LogUart.txt', mode='a',encoding='utf-8') as LogUart:
            LogUart.writelines([time.ctime(), '  log是 :',log])
            LogUart.close()
        # myinput=bytes([0X01,0X03,0X00,0X00,0X00,0X01,0X84,0X0A])    # 需要发送的十六进制数据
        # print(myinput)
        # ser.write(myinput)    # 用write函数向串口发送数据   只能发送16进制

#/////////////////////////////////////////////////////////////////////////////////////


def faSong():   # 发送函数
    while True: # 循环发送数据
        time.sleep(2)   # 设置发送间隔时间
        myinput=bytes([0X01,0X03,0X00,0X00,0X00,0X01,0X84,0X0A])    # 需要发送的十六进制数据
        # myinput = 'AT+TIME=1600865134\n'
        ser.write(myinput)    # 用write函数向串口发送数据



#多线程
def main():   
    # SpeechThread = threading.Thread(target=Speech)
    # SpeechThread.daemon=True    #设置线程为守护线程
    # SpeechThread.start()

    # SaveExcelThread=threading.Thread(target=SaveExcel)
    # SaveExcelThread.daemon=True
    # SaveExcelThread.start()

    # SaveExcelThread=threading.Thread(target=faSong)
    # SaveExcelThread.daemon=True
    # SaveExcelThread.start()

    UartDataThread=threading.Thread(target=UartData)
    UartDataThread.daemon=True
    UartDataThread.start()

main()
# UartData()


input()