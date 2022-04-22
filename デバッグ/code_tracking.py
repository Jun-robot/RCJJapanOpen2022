import sensor, image, time
# Color Tracking Thresholds (L Min, L Max, A Min, A Max, B Min, B Max)
thresholds = [(30, 50, -22, 0, -11, 0)]
# You may pass up to 16 thresholds above. However, it's not really possible to segment any
# scene with 16 thresholds before color thresholds start to overlap heavily.
x_data=0
y_data=0
area_data = 0

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 300)
sensor.set_saturation(3)
sensor.set_contrast(3)
sensor.set_brightness(1)
sensor.set_vflip(True)
sensor.set_hmirror(True)
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False) # must be turned off for color tracking
clock = time.clock()

# Only blobs that with more pixels than "pixel_threshold" and more area than "area_threshold" are
# returned by "find_blobs" below. Change "pixels_threshold" and "area_threshold" if you change the
# camera resolution. Don't set "merge=True" becuase that will merge blobs which we don't want here.

while(True):
    clock.tick()
    img = sensor.snapshot()
    for blob in img.find_blobs(thresholds, pixels_threshold=200, area_threshold=200):
        img.draw_rectangle(blob.rect())
        img.draw_cross(blob.cx(), blob.cy())
        x_data=blob.cx()
        y_data=blob.cy()
        area_data =blob.area()
    print("fps=%d" % clock.fps()),
    print(" x=%d" % x_data),
    print(" y=%d" % y_data),
    print(" rect=%d" % area_data)
