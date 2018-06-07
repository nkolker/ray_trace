CC = g++
CCFLAGS = -g -Wall -std=c++11

ray_trace: Render.o Ray.o Camera.o Vector4.o Matrix4_4.o Sphere.o
	$(CC) -o ray_trace $(CCFLAGS) Render.o Ray.o Camera.o Vector4.o Matrix4_4.o Sphere.o

# Add whatever additional files you want with a rule here, and also
# in the final linking rule above.

Render.o: Render.cc Render.h
	$(CC) $(CCFLAGS) -c Render.cc

Ray.o: Ray.cc Ray.h
	$(CC) $(CCFLAGS) -c Ray.cc

Camera.o: Camera.cc Camera.h
	$(CC) $(CCFLAGS) -c Camera.cc

Vector4.o: Vector4.cc Vector4.h
	$(CC) $(CCFLAGS) -c Vector4.cc

Matrix4_4.o: Matrix4_4.cc Matrix4_4.h
	$(CC) $(CCFLAGS) -c Matrix4_4.cc

#Object3D.o: Object3D.cc Object3D.h
#	$(CC) $(CCFLAGS) -c Object3D.cc

Sphere.o: Sphere.cc Sphere.h
	$(CC) $(CCFLAGS) -c Sphere.cc

clean:
	-rm *.o ray_trace

