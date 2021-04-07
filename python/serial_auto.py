import serial
# # ①选择设备
# ser=serial.Serial("/dev/ttyUSB0",9600,timeout=0.5) #使用USB连接串行口
# ser=serial.Serial("/dev/ttyAMA0",9600,timeout=0.5) #使用树莓派的GPIO口连接串行口
# ser=serial.Serial(1,9600,timeout=0.5)#winsows系统使用com1口连接串行口
# ser=serial.Serial("com1",9600,timeout=0.5)#winsows系统使用com1口连接串行口
# ser=serial.Serial("/dev/ttyS1",9600,timeout=0.5)#Linux系统使用com1口连接串行口
# print (ser.name)#打印设备名称
# print (ser.port)#打印设备名
# ser.open()
# #打开端口
# s = ser.read(10)#从端口读10个字节
# ser.write("hello")#向端口写数据
# ser.close()#关闭端口

# while(1)
#     print('a\n')
ser=serial.Serial() #使用USB连接串行口

print("请输入正确的串口号按回车健运行：")
MycomX='COM'+str(input())

ser.port =MycomX # 串口
print(ser.name)


ser.baudrate = 1500000  #波特率
ser.bytesize = 8
ser.parity = serial.PARITY_NONE
ser.stopbits = 1
ser.open() # 开启串口

def UartData():
    while True:
        #ch = ser.read() # 收一个bytes
        ch=ser.readline()#读取以“\n”结尾的行
        log_can=ch.decode(encoding='utf-8')
        print(ch)



UartData()
# def main():
#     while True:
#         print('a\n')


# main()
input()