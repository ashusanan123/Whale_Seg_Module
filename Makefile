all: Seg_Whale_Compiled

Seg_Whale_Compiled: HSV_Thresholding.o Find_Seg_Whale.o
	g++ Main_Code.cpp HSV_Thresholding.o Find_Seg_Whale.o -o Seg_Whale_Compiled `pkg-config --cflags --libs opencv`

HSV_Thresholding.o:
	g++ -c HSV_Thresholding.cpp

Find_Seg_Whale.o:
	g++ -c Find_Seg_Whale.cpp

clean:
	rm -rf *.o Seg_Whale_Compiled