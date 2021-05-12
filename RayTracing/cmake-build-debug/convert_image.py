import PythonMagick as PM

img = PM.open('./image.ppm')
img.write('./image.jpg')

print('---convertion finished---')