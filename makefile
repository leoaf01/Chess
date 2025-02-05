all: compile link move

compile:
	g++ -ISFML-3.0.0/include -DSFML_STATIC -c src/*.cpp

link:
	g++ *.o -o main.exe -LSFML-3.0.0/lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -static

move:
	mv *.o ./output

clean:
	rm output/*.o main.exe