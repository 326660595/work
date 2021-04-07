import math
import time


#open('test.txt', mode='w',encoding='utf-8')

wf = open('test.txt', 'w', encoding='utf-8')


wf.write('Tom\n')
wf.writelines(['Hello\n', 'Python\n'])
i=1
# str1='a'
# str1=str(i)
# print(str1)
# wf.write(str1)
while True:
    str1='a'
    i+=2
    str1=str(i)
    print(str1)
    #open('test.txt', mode='w',encoding='utf-8')
    wf.write(time.ctime())
    #print(time.ctime())
    wf.write(str1)
    wf.write('\n')



# 关闭
wf.close()

input()