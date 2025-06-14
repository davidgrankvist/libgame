# Concepts, Tips and Tricks

Below are some game programming concepts, tips and tricks that were helpful when implementing this library.

## Platform Layer

The goal of a platform layer is to provide a common abstraction that's compatible with different platforms. The game calls the abstraction
which then calls into the relevant platform specific functions.

### Structure

Internally, the platform layer needs to figure out which platform specific functions to call. There are two main ways to handle this:

1. use ifdefs at build time
2. use function pointers at runtime

With ifdefs, you can have a single library entrypoint and include the relevant code for the build target. 
The drawback of using ifdefs is that it's easy to end up with a lot of them spread out in the code base, which makes porting challenging.

With function pointers, you can have platform specific library entrypoints that set up the relevant functions for the current build target.
Then the platform independent code can call whatever function pointers were provided, without having to know which platform it calls into.

It's also valid to use a combination of the two approaches, because some parts need to be set up at build time (for example library exports).

#### Platform specific main

Some platforms require a specific main function, like WinMain on Windows. This means that both the library code and
game code need to own some platform specific code. To deal with this when using function pointers, you can let the library
expose a platform specific initialization function which is then called from the platform main.

One trick to hide the platform specific main from the game code is to add an ifdef in a library header that automatically includes a WinMain. In WinMain the platform initialization and game code main can be invoked. This way the game code runs a "fake main" that was actually called from WinMain.

### Input

When you press a key, it will be reported to the OS using a platform-specific virtual key code.
You can map those to your own platform-independent key codes and then store input states
based on that. This allows you to share input state management between different platforms.

### OpenGL

OpenGL has two parts:

1. platform-specific initialization
2. platform-independent render backend calls (if the version is supported)

Each platform is responsible for things like setting up the OpenGL context. The render backend can be shared between some platforms,
but it is not entirely platform-independent since different platforms support different versions of OpenGL.

## Graphics

### Default shader program

For simple rendering, the client code may not need a custom shader. Instead, your render backend can provide high-level functions for drawing shapes
and pass those as input to a default shader program.

The default vertex shader can take in the vertex position, color, a custom transform and other projections.
This way, the client code can implement simple graphics without worrying about the underlying shader implementation.

### Batching draw calls

Each draw call comes with overhead, so ideally you want to make a few draw calls with lots of vertex data.

One simple approach to batching is to preallocate a buffer that is populated with vertex data each frame. This can for example
be vertices that should be drawn as triangles. When it's time to draw, you can check how much of the buffer was populated during
that frame, transmit all of that data at once and issue the draw call.

Sometimes you need multiple draw calls, for example when you want to change the value of a uniform or run different shader programs.
In that case, you can have a similar scheme but also keep track of a start index for the next draw call.

### Normalized device coordinates

In games, there are different approaches to coordinate systems. A 2D game may use screen coordinates with an inverted Y axis.
A 3D game may use more abstract world coordinates, which has different conventions for the orientation.

Graphics APIs need a way to figure out where on the screen to draw things, regardless of 2D or 3D graphics.
All of the 2D coordinates need to be expressed relative to the screen. All of the abstract 3D shapes need to be
projected onto the 2D screen surface. To make the 2D screen space consistent regardless of world coordinate conventions
and screen resolutions, there is a system called Normalized Device Coordinates (NDC). In OpenGL, this is in the -1 to 1 range.

The NDC space essentially defines a cube of visible graphics. The X and Y coordinates deteremine where on the screen
graphics end up. The Z coordinate can be used to figure out how to stack things (depth testing). Anything outside of
the NDC range is not visible.

### Frustum

In graphics, a frustum is a way to express a visible part of 3D space. Basically you take two parallel planes and connect the corners
to get a 3D shape. If the planes have the same size, you get a cube-like shape. If one is smaller, you get a pyramid with the top sliced off.
The two planes are called the "near" and "far" planes.

Mathematically, a frustum has a more general definition. The 2D shapes you connect can be something else, like pentagons.
In graphics though, they're usually planes.

### Orthographic projection

Orthographic projection is a transform for when the frustum is cube-like. It converts directly from world coordinates
to NDC. It is flexible enough that you can decide things like Y axis direction and whether you have a left- or right-handed
system.

### Perspective projection

Imagine that you look down a straight road towards the horizon. Points further away will be closer together
so that from your point of view the road has a triangular shape. This effect is called perspective.

In 3D graphics, there is a transform to get this effect called perspective projection. It uses a pyramid-like frustum
where the near plane is small and the far plane is large. When this shape is normalized to the NDC cube this will cause
things far away to be squished together, which gives the perspective effect.

The perspective projection doesn't do the final squishing. It outputs coordinates in clip space, which means that
they are points in the pyramid-like frustum that have an extra w component that can be used to normalize the values to NDC.
This last step is called the perspective divide. OpenGL does the perspective divide automatically.

### Camera

A camera is essentially a transform. It converts world coordinates to coordinates that are relative to what the camera is looking at.
The camera system takes some parameters and outputs a transformation matrix that the render backend can apply in the vertex shader code.

In 2D the camera transform defines a viewport, scaling and rotation. The viewport is the final step and can be computed with orthographic projection with
placeholder near/far planes (as Z is ignored).

In 3D the camera has a position, a target it looks towards and an upwards direction (as well as some other parameters to define a frustum). There are two major steps in the transform.
First coordinates need to be moved so that the camera position is the origin (view transform). Then the coordinates need to transformed
to take into account the frustum. If you want a perspective effect, use perspective projection. If not, use orthographic projection.

A 3D camera can have different kinds of movements and rotation, for example first person or orbiting around a target.
These kinds of movements can be implemented by modifying the position/target/up vectors before doing the view transform.
The game code can opt in to the position/target/up calculations that are relevant and after that the camera transform is calculated
as usual.

## Hot reloading

To speed up the feedback loop, you can reload game code while the game is running. Here's one way:
1. separate the per-frame game update code from the game loop
2. build the game update code as a dynamic library
3. in the game loop, reload that library when it has changed
4. assign a function pointer to the reloaded game update function

The platform layer can support the game code with the library loading utilities.

One caveat is locked files. The application will lock the loaded library and the debugger might lock the debug symbol file. You can work around this by copying the original files to temporary files and loading the copies instead.
