from time import sleep
from random import randrange
from threading import Thread, Event

# 自定义生产者线程类
class Producer(Thread):
    def __init__(self, threadname):
        Thread.__init__(self, name=threadname)

    def run(self):
        for _ in range(5):
            # 随机等待 0~4 秒
            sleep(randrange(5))
            # 缓冲区满则等待
            if eventFull.isSet():
                print('Producer is waiting...')
                eventFull.wait()  # 等待缓冲区被清空
            # 开始生产
            print('Producing...')
            lst.extend(range(10))  # 向缓冲区放入 10 个数据
            eventFull.set()  # 设置缓冲区满
            eventEmpty.clear()  # 允许消费者消费

# 自定义消费者线程类
class Consumer(Thread):
    def __init__(self, threadname):
        Thread.__init__(self, name=threadname)

    def run(self):
        for _ in range(5):
            # 随机等待 0~4 秒
            sleep(randrange(5))
            # 缓冲区空则等待
            if eventEmpty.isSet():
                print('Consumer is waiting...')
                eventEmpty.wait()  # 等待缓冲区有数据
            # 开始消费
            print(f'Consuming... {lst}')
            lst.clear()  # 清空缓冲区
            eventEmpty.set()  # 设置缓冲区空
            eventFull.clear()  # 允许生产者生产

# 初始化缓冲区
lst = []
eventFull = Event()  # 缓冲区满标志
eventEmpty = Event()  # 缓冲区空标志
eventEmpty.set()  # 初始化为空状态

# 启动线程
Producer('Producer').start()
Consumer('Consumer').start()
