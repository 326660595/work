import serial
import threading
import time
import os
import re
import fileinput
from glob import glob
import subprocess as sp
from queue import Queue

# import xlsxwriter
# import xlrd
from openpyxl  import load_workbook
from openpyxl import Workbook


print('Hellow World:',time.time()) #时间戳：秒

TheTimeIs=time.ctime()
event = threading.Event()
q=Queue(1)
q1=Queue(1)
# q2=Queue(1)
#//////////////////////////////////////////////////////////////////////////////调用powershell的类
class PowerShell:
    # from scapy
    def __init__(self, coding, ):
        cmd = [self._where('PowerShell.exe'),
               "-NoLogo", "-NonInteractive",  # Do not print headers
               "-Command", "-"]  # Listen commands from stdin
        startupinfo = sp.STARTUPINFO()
        startupinfo.dwFlags |= sp.STARTF_USESHOWWINDOW
        self.popen = sp.Popen(cmd, stdout=sp.PIPE, stdin=sp.PIPE, stderr=sp.STDOUT, startupinfo=startupinfo)
        self.coding = coding

    def __enter__(self):
        return self

    def __exit__(self, a, b, c):
        self.popen.kill()

    def run(self, cmd, timeout=6):                                         #timeout=0  延时
        b_cmd = cmd.encode(encoding=self.coding)
        try:
            b_outs, errs = self.popen.communicate(b_cmd, timeout=timeout)
        except sp.TimeoutExpired:
            self.popen.kill()
            b_outs, errs = self.popen.communicate()
        outs = b_outs.decode(encoding=self.coding)
        return outs, errs

    @staticmethod
    def _where(filename, dirs=None, env="PATH"):
        """Find file in current dir, in deep_lookup cache or in system path"""
        if dirs is None:
            dirs = []
        if not isinstance(dirs, list):
            dirs = [dirs]
        if glob(filename):
            return filename
        paths = [os.curdir] + os.environ[env].split(os.path.pathsep) + dirs
        try:
            return next(os.path.normpath(match)
                        for path in paths
                        for match in glob(os.path.join(path, filename))
                        if match)
        except (StopIteration, RuntimeError):
            raise IOError("File not found: %s" % filename)
#//////////////////////////////////////////////////////////////////////////


#/////////////////////////////////////////////////////////////////////////文本处理
pscmd='Add-Type -AssemblyName System.speech;\
            $speak = New-Object System.Speech.Synthesis.SpeechSynthesizer;\
            $speak.Rate = 0;\
            $speak.Speak("天猫精灵")'               #powershell文本朗读指令

cmd="天猫精灵"
StandardCmd_n=''
# Number_n=0
SuccessNum_n=0
FailDispaly_n=[]
uart_error=0                #控制，朗读10次天猫精灵都没有回应，退出程序
cmd_error=0

data = load_workbook('test.xlsx')#打开表格
mydata=data["Sheet1"]         #sheet1

log=''      #提取日志


def SpeakTm(): 
    global uart_error                                  #读天猫
    with PowerShell('GBK') as ps:    
        ps.run(pscmd)
        print("天猫精灵") 
        uart_error+=1
        if uart_error>10:       #朗读10次没有回应，保存信息，退出程序
            data.save('TestResult.xlsx')
            os._exit(0)
        with open('Show.txt', mode='a',encoding='utf-8') as LogUart:
            LogUart.writelines(["天猫精灵\n"])
            LogUart.close()


def changepscmd(fcmd):                           #读设定朗读语句
    cmd=str(fcmd)
    pscmd0=pscmd
    p = re.compile("天猫精灵")
    pscmd1 = p.sub(cmd,pscmd0)

    with PowerShell('GBK') as ps:
        #time.sleep(1)
        outs, errs = ps.run(pscmd1)              #在run函数中输入powershell指令
        print('error:', os.linesep, errs)
        print('output:', os.linesep, outs)
        # with open('LogSpeech.txt', mode='a',encoding='utf-8') as LogSpeech:
        #     LogSpeech.writelines([time.ctime(), '  say :',cmd,'\n'])
        #     LogSpeech.close()
        with open('Show.txt', mode='a',encoding='utf-8') as LogUart:
            LogUart.writelines([time.ctime(), '  say :',cmd,'\n'])
            LogUart.close()
        print(cmd) #打印朗读的语料

def checkcmd(StandardCmd_n):                    #比较提取的指令和标准指令
    global SuccessNum_n
    global FailDispaly_n
    # q2.get()
    p = re.compile(", 0x")
    pscmd0 = p.sub('',log)
    pscmd1=pscmd0.upper()
    scmd0=str(StandardCmd_n)
    scmd=scmd0.upper()
    print('yu--->',cmd,'pscmd1--->',pscmd1,'standard--->',StandardCmd_n)
    with open('Show.txt', mode='a',encoding='utf-8') as LogUart:
                    LogUart.writelines(['yu--->',cmd,'pscmd1--->',pscmd1,'standard--->',StandardCmd_n])
                    LogUart.close()
    if pscmd1.find(scmd)!=-1:
        return True
    else:
        return False

def Rouse_Tm(log):
    if log.find('tian mao jing ling')!=-1:
        return True
    else:
        return False




#//////////////////////////////////////////////////////////////////////////////////朗读线程函数入口
def Speech():
    global StandardCmd_n  
    global Corpus_n 
    global order   
    order=1
   
    for i in mydata['A']:
        if order > 1:                   #使得order读取的数据和i的下标同步，好自然结束for循环
            Corpus_n=str(i.value)     #取语料
            StandardCmd_n=str(mydata['B%d'%order].value)   #取语料对应的标准指令

            Number_n=mydata['C%d'%order].value             #取语料对应的朗读次数
            if Number_n==None:
                Number_n=0
            print(Number_n)
            SuccessNum_n=0                          #初始成功次数置0
            FailDispaly_n=""                        #初始失败次数置空
            FailSum=0
            error_check=0
            
            while Number_n>0:   #朗读次数大于0朗读，并递减
                SpeakTm()
                time.sleep(1)                   #使线程等待收到相应天猫响应指令后继续执行
                
                print(time.ctime())    
                event.wait(7)    #线程等待触发
                print(time.ctime())

                if q.empty():
                    print('cant listen') 
                    continue                     #天猫精灵没有唤醒，重新进行唤醒       
                else:
                    q.get()
                    print('good')
                    
                event.clear()                   #set会重置所有wait为不再等待，clear使所有wait重新生效
                changepscmd(Corpus_n)           #朗读
                Number_n-=1
                # time.sleep(5)                   #必须有个时间等待接收指令
                
                print(time.ctime())    
                event.wait(10)                  #线程等待触发
                print(time.ctime())
                event.clear()

                if q1.empty():
                    print('cant know')                   #天猫精灵唤醒成功，朗读语料，没有回应相关的指令
                    error_check+=1
                    with open('Show.txt', mode='a',encoding='utf-8') as LogUart:
                        LogUart.writelines([time.ctime(), 'cant know\n'])
                        LogUart.close()
                    if cmd_error==2:
                        if FailSum<10:
                            FailSum+=1
                            FailDispaly_n+="识别T 发送F- \n"
                            mydata['E%d'%order].value=FailDispaly_n     #直接写入没有识别进行下一次朗读 
                    else:
                        if FailSum<10:
                            FailSum+=1
                            FailDispaly_n+="识别错误- \n"
                            mydata['E%d'%order].value=FailDispaly_n     #直接写入没有识别进行下一次朗读        
                else:
                    q1.get()
                    print('good')
                    with open('Show.txt', mode='a',encoding='utf-8') as LogUart:
                        LogUart.writelines([time.ctime(), 'good\n'])
                        LogUart.close()
                    if checkcmd(StandardCmd_n):     #判断指令是否正确，正确添加成功数，不正确打印错误案例
                        error_check=0
                        SuccessNum_n+=1
                    else:
                        error_check+=1
                        if FailSum<10:
                            FailSum+=1
                            FailDispaly_n+=log+'\n'
                            mydata['E%d'%order].value=FailDispaly_n  
                if error_check>=10:
                    break     
                mydata['D%d'%order].value=SuccessNum_n       #直接将所获得得数据输入对应单元格
                try:
                    data.save('TestResult.xlsx')#保存到一个新的excel 
                except():
                    os._exit(0)
                           
        order+=1

    time.sleep(5)
    os._exit(0)


    


#/////////////////////////////////////////////////////////////////////////////////////串口调试
ser = serial.Serial()

print("请输入正确的串口号按回车健运行：")
MycomX='COM'+str(input())

ser.port =MycomX # 串口
print(ser.name)


ser.baudrate = 1500000  #波特率
ser.bytesize = 8
ser.parity = serial.PARITY_NONE
ser.stopbits = 1
ser.open() # 开启串口

#///////////////////////////////////////////////////////////////////////////////////主线程串口接收
def UartData():

    global uart_error
    global cmd_error 
    global log 
    while True:
        #ch = ser.read() # 收一个bytes
        ch=ser.readline()#读取以“\n”结尾的行
        log_can=ch.decode(encoding='utf-8')
        itlog=log_can.find('send')

        error_1=log_can.find('fresult') #接收到指令的特征
        with open('LogUart.txt', mode='a',encoding='utf-8') as LogUart:
                LogUart.writelines([time.ctime(), ' ',log_can])
                LogUart.close()                                              #
        if Rouse_Tm(log_can):
            print("Tm已唤醒：")
            uart_error=0
            with open('Show.txt', mode='a',encoding='utf-8') as LogUart:
                    LogUart.writelines([time.ctime(), 'Tm已唤醒：\n'])
                    LogUart.close()
            if q.empty():
                q.put(1)            #使用queue队列来完成线程之间的通信，queue是线程安全的
                event.set()         
                # event.clear()

    
        if itlog==0:
            cmdl=len(log_can)
            if cmdl==104:
                log=log_can
                cmd_error=1
                print('cmdlen is:\n',len(log),'\n')
                print('log is-----> %s' % log)
                with open('Show.txt', mode='a',encoding='utf-8') as LogUart:
                    LogUart.writelines([time.ctime(), 'log is----->',log,'\n'])
                    LogUart.close()

                if q.empty():
                    q1.put(1)            #使用queue队列来完成线程之间的通信，queue是线程安全的
                    event.set()


        if cmd_error==0 and error_1!=-1:
            print('error_1log-->',log_can)
            cmd_error=2

 
            




            
               
            
            

#/////////////////////////////////////////////////////////////////////////////////////


#多线程
SpeechThread=threading.Thread(target=Speech)
#SpeechThread.daemon=True    #设置线程为守护线程
UartDataThread=threading.Thread(target=UartData)
#UartDataThread.daemon=True

def main():  
    UartDataThread.start()
    SpeechThread.start()
    time.sleep(60*60*24)        #主函数结束，会导致线程结束，通过休眠主函数让线程继续运行，线程朗读运行完毕通过 os._exit（）结束程序

    
if __name__ == '__main__':
    main()


#
