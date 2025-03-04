all: compile move link

compile:
	g++ -g -ISFML-3.0.0/include -DSFML_STATIC -c src/*.cpp 

move:
	mv *.o ./output

link:
	g++ output/*.o -o main.exe -LSFML-3.0.0/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -static

clean:
	rm output/*.o