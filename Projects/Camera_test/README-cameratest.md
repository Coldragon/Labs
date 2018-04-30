SDL2 Camera system / engine

Dependency : -SDL2
             -SDL2_image
             -SDL2_ttf
             
Made with Visual Studio 2017 and tested on Ubuntu bundgie 17.04 with gcc

Function : 
	- Can load .json map (res/map/map.json) made in Tiled (With two layer for now) (100*100 The array is static for now)
	- Camera movable in the "fictive" coordinate system
	- Sprite can be show in the "fictive" world
	- Function that translate any x,y fictive into screen x,y
	- Gui can be show and will be stick to the screen
	- Rectangle GUI with a 9 tile gui can be easly made
	- Camera collide at the edge of the world
	- there is a game.time.delta that help to move x per seconds and not per frame
	- FPS limiter
	- Resizable window with adaptable content
	- Polar movement from Point 1 to Point 2, and you move by R everytime the function is called (Press Space to try)

echap : enable/disable input grab of the window (block mouse in the windows)
move : ZQSD or WASD or ARROW or with mouse at the edge of the screen (only work if input grab is enabled)
space : move to the center of the map

tileset by : KENNEY



