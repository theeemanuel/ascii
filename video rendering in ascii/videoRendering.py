import os
import sys
import cv2
import PIL.Image

chars = "@#S%?*+;:,."
newWidth=100

def resize(image):
    width, height = image.size
    ratio = height/width
    newHeight = int(newWidth * ratio)
    resized_image = image.resize((newWidth, newHeight))
    return(resized_image)

def grayscale(image):
    grayscaleImage = image.convert("L")
    return(grayscaleImage)
    
def ascii(image):
    pixels = image.getdata()
    characters = "".join([chars[pixel//25] for pixel in pixels])
    return(characters)

def framer(image):
    newImage = ascii(grayscale(resize(image)))
    pixelCount = len(newImage)  
    asciiImage = "\n".join([newImage[index:(index+newWidth)] for index in range(0, pixelCount, newWidth)])
    sys.stdout.write(asciiImage)
    os.system('cls' if os.name == 'nt' else 'clear') 

def main(new_width=100):
    run = True
    while run:
        path = str(input("Paste the image path: "))
        try:
            video = cv2.VideoCapture(path)
        except Exception:
            print(path, " is not a valid pathname to an image.")
            pass

        play = True     
        while play:
            try:
                ret, frame = video.read()
                cv2.imshow("frame",frame)
                framer(PIL.Image.fromarray(frame))
                cv2.waitKey(10)
            except:
                play = False

        redo = str(input("Have another file? (y/n): "))
        if redo == 'y' or redo == 'Y':
            print("______________________________________________________________________________")
            run = True
        else:
            run = False
 
main()
