import serial,pymysql,threading,time
x=serial.Serial('com21',115200,timeout=1)
def faSong():   # 发送函数
    while True: # 循环发送数据
        time.sleep(3)   # 设置发送间隔时间
        myinput=bytes([0X01,0X03,0X00,0X00,0X00,0X01,0X84,0X0A])    # 需要发送的十六进制数据
        x.write(myinput)    # 用write函数向串口发送数据

def jieShou():  # 接收函数
    while True: # 循环接收数据
        while x.inWaiting()>0:  # 当接收缓冲区中的数据不为零时，执行下面的代码
            myout=x.read(7) # 提取接收缓冲区中的前7个字节数
            print(myout.decode('gbk'))
            # 以下是用到三目运算符、map函数和lambda函数，
            # 代码作用是将接收到的数据每一个转换成十六进制，中间用/x分割，便于后面分割
            datas=''.join(map(lambda x:('/x' if len(hex(x))>=4 else '/x0')+hex(x)[2:],myout))
            print(datas)
            new_datas=datas[2:].split('/x') # 由于datas变量中的数据前两个是/x，所以用到切片工具
            need=''.join(new_datas) # 将前面的列表中的数据连接起来
            saveSql(need)

def saveSql(a):  # 保存接收的数据
    # time.time返回当前时间的时间戳,即1234892919.655932这种类型
    sql = "INSERT INTO VOC_DATA(value,create_time) VALUES (" + str(a) + "," + str(int(time.time())) + ")"
    cursor.execute(sql)
    db.commit()
    x.flushInput()

if __name__ == '__main__':
    # 打开数据库连接
    db=pymysql.connect(host='localhost', user='root', password='root',
                 database='xwl_test', port=3306, )
    # 使用sursor()方法创建一个游标对象cursor
    cursor=db.cursor()
    t1=threading.Thread(target=jieShou)　　# 创建一个线程1：不断的去请求数据
    t2=threading.Thread(target=faSong)　　# 创建一个线程2：不断的去发送数据
    t2.start()　　# 开启线程2
    t1.start()　　# 开启线程1