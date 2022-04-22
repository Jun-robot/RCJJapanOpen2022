import pyb, ustruct
from pyb import UART
import sensor, image, time

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
clock = time.clock()

uart = UART(3, 19200)


while(True):
    x = 100
    try:
        uart.write(ustruct.pack('B',x))
    except OSError as err:
        pass

    clock.tick()
    img = sensor.snapshot()
    print(clock.fps())



