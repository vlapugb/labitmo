import time 

def calc(x):
    return pow(x, 2) - pow(x, 2) + pow(x, 4) - pow(x, 5) + x + x

print("Введите x:")
x = float(input()) 

print("Введите n:")
n = int(input())  

start = time.time()

for i in range(0, n):
    calc(i)  

end = time.time()

res_time = int((end - start) * 10**9)

print("Программа выполнилась за", res_time," наносекунд")