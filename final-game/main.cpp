/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, vectors, and strings

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <direct.h>
#include <time.h>
#define GetCurrentDir _getcwd

#else

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

#endif

#include <iostream>
#include <stdio.h>
#include <string>
#include "Text.h"
#include "LTexture.h"
#include "Color.hpp"
#include "Sprite.h"
#include "Vector2d.h"
#include "Util.h"
#include "IMovingEntity.h"
#include "SteeringManager.h"
#include "Menu.h"


using namespace std;

//The dimensions of the level
const int LEVEL_WIDTH = 4000;
const int LEVEL_HEIGHT = 2250;

const int MENU_HEIGHT = 95;
bool isGamePaused = true;
//Main loop flag
bool quit = false;

//The dot that will move around on the screen
class Dot : public IMovingEntity
{
public:
    //The dimensions of the dot
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;

    //Maximum axis velocity of the dot
    static const int DOT_MAX_SPEED = 10;

    //Initializes the variables
    Dot();

    //Takes key presses and adjusts the dot's velocity
    void handleEvent(const SDL_Event &e);

    //Moves the dot
    void move();

    //Shows the dot on the screen relative to the camera
    void render(const int camX, const int camY);

    //Position accessors
    int getPosX();

    int getPosY();

    void Update(const double d_time);

    void updatePosition(const double d_time);

    void updateVelocity(const double d_time);

    void setMovement(const E_Movement movement);

    void setStopping(const E_Movement movement);

    int getCollectable(Dot &obj);

    /* Implement required methods from IMovingEntity */
    virtual Vector2d getVelocity() { return m_velocity; }

    virtual Vector2d getPos() { return m_position; }

    // \FIXME Not the best way, duplicated code may indicate code smell...
    virtual void setVelocity(Vector2d vel) { m_velocity = vel; }

    virtual void setPos(Vector2d pos) { m_position = pos; }


    void setM_velocity(Vector2d const &m_velocity)
    {
        Dot::m_velocity = m_velocity;
    }

    Vector2d const &getM_velocity() const
    {
        return m_velocity;
    }

    bool isToRender() const
    {
        return toRender;
    }

    void setToRender(bool toRender)
    {
        Dot::toRender = toRender;
    }

    Vector2d const &getM_position() const
    {
        return m_position;
    }

    void setM_position(Vector2d const &m_position)
    {
        Dot::m_position = m_position;
    }

    bool IsCollectable() const
    {
        return isCollectable;
    }


    SteeringManager *getSteering() const
    {
        return steering;
    }

private:
    Vector2d m_position, m_velocity;
    E_Movement m_current_movement, m_previous_movement;
    double m_current_speed, m_drag_coefficient;
    bool m_isAccelerating, m_isMoving;
    bool toRender;
    bool isCollectable;
    SteeringManager *steering;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The window renderer
SDL_Renderer *gRenderer = NULL;

//Scene textures
LTexture gDotTexture, gBGTexture, gBGTextureValley,
        gInfoMenuBar, gInfoMenuBarShadow;

Sprite gMenu;

Dot::Dot()
{
    //Initialize the offsets
    m_position.x = 240;
    m_position.y = 120;

    //Initialize the velocity
    m_velocity.x = 0;
    m_velocity.y = 0;

    m_current_movement = m_previous_movement = E_STOPPED;
    toRender = true;
    isCollectable = true;
    steering = new SteeringManager(this);
}

void Dot::handleEvent(const SDL_Event &e)
{
    cout << m_velocity.x << endl;

    //If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        //Adjust the velocity
        switch (e.key.keysym.sym) {
            case SDLK_UP: {
                setMovement(E_UP);
                break;
                //m_velocity.x -= 5;
            }
            case SDLK_DOWN: {
                setMovement(E_DOWN);
                break;
                //m_velocity.x += 5;
            }
            case SDLK_LEFT: {
                setMovement(E_LEFT);
                break;
                //m_velocity.y -= 5;
            }

            case SDLK_RIGHT: {
                setMovement(E_RIGHT);
                break;
                //m_velocity.y += 5;
            }

        }
    }
        //If a key was released
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        //Adjust the velocity
        switch (e.key.keysym.sym) {
            case SDLK_UP: {
                setStopping(E_UP);
                break;
            }
            case SDLK_DOWN: {
                setStopping(E_DOWN);
                break;
            }
            case SDLK_LEFT: {
                setStopping(E_LEFT);
                break;
            }
            case SDLK_RIGHT: {
                setStopping(E_RIGHT);
                break;
            }
        }
    }
}

void Dot::move()
{
    //Move the dot left or right
    m_position.x += m_velocity.x;

    //If the dot went too far to the left or right
    if ((m_position.x < 0) || (m_position.x + DOT_WIDTH > LEVEL_WIDTH)) {
        //Move back
        m_position.x -= m_velocity.x;
    }

    //Move the dot up or down
    m_position.y += m_velocity.y;

    //If the dot went too far up or down
    if ((m_position.y < 0) || (m_position.y + DOT_HEIGHT > LEVEL_HEIGHT)) {
        //Move back
        m_position.y -= m_velocity.y;
    }
}

void Dot::render(const int camX, const int camY)
{
    if (toRender) {
        //Show the dot relative to the camera
        gDotTexture.render(m_position.x - camX, m_position.y - camY);
        gMenu.render(0, SCREEN_HEIGHT - MENU_HEIGHT);
        gInfoMenuBarShadow.render(1, SCREEN_HEIGHT - MENU_HEIGHT + 6);
        gInfoMenuBar.render(0, SCREEN_HEIGHT - MENU_HEIGHT + 5);
    }
}

int Dot::getPosX()
{
    return m_position.x;
}

int Dot::getPosY()
{
    return m_position.y;
}

void Dot::Update(const double d_time)
{
    m_current_speed = (m_velocity.x * m_velocity.x) + (m_velocity.y * m_velocity.y);
    m_current_speed = sqrt(m_current_speed);

    if (m_current_speed < 0.1) {
        m_velocity.x = m_velocity.y = 0.0f;
        m_current_speed = 0;
    }

    if (m_current_speed > DOT_MAX_SPEED) {
        m_velocity.x /= m_current_speed;
        m_velocity.y /= m_current_speed;

        m_current_speed = DOT_MAX_SPEED;

        m_velocity.x *= m_current_speed;
        m_velocity.y *= m_current_speed;
    }

    steering->update();
    updateVelocity(d_time);
    updatePosition(d_time);
}

void Dot::updateVelocity(const double d_time)
{
    Vector2d acceleration;

    if (m_current_movement == E_UP) {

        if (m_previous_movement == m_current_movement)
            m_velocity.y -= -5;
        else
            acceleration.y = 1.2f;
    }

    if (m_current_movement == E_DOWN) {
        m_velocity.y = 5;

        if (m_previous_movement == m_current_movement)
            m_velocity.y += 5;

        acceleration.y = 1.2f;
    }

    if (m_current_movement == E_LEFT) {
        m_velocity.x = -5;

        if (m_previous_movement == m_current_movement)
            m_velocity.x -= 5;

        acceleration.x = 1.2f;
    }

    if (m_current_movement == E_RIGHT) {
        m_velocity.x = 5;

        if (m_previous_movement == m_current_movement)
            m_velocity.x += 5;

        acceleration.x = 1.2f;
    }

    //FIXME clearing vel prevents followLeader behavior to work properly
    if (d_time == 0) {
        m_velocity.x *= acceleration.x;
        m_velocity.y *= acceleration.y;
    }
    else {
        m_velocity.x *= acceleration.x * d_time;
        m_velocity.y *= acceleration.y * d_time;
    }

}


void Dot::updatePosition(const double d_time)
{
    if (d_time == 0) {
        m_position.x += m_velocity.x;
        m_position.y += m_velocity.y;
    }
    else {
        m_position.x += m_velocity.x * d_time;
        m_position.y += m_velocity.y * d_time;
    }

    if ((m_position.x < 0) || (m_position.x + DOT_WIDTH > LEVEL_WIDTH))
        m_position.x -= m_velocity.x;

    if ((m_position.y < 0) || (m_position.y + DOT_HEIGHT > LEVEL_HEIGHT))
        m_position.y -= m_velocity.y;
}


void Dot::setMovement(const E_Movement movement)
{
    m_previous_movement = m_current_movement;
    m_current_movement = movement;
}

void Dot::setStopping(const E_Movement movement)
{

    if (m_current_movement == E_UP) {
        if (m_velocity.y < 0)
            m_velocity.y = m_velocity.x / 2;
    }

    if (m_current_movement == E_DOWN) {
        if (m_velocity.y > 0)
            m_velocity.y = m_velocity.y / 2;
    }

    if (m_current_movement == E_LEFT) {
        if (m_velocity.x < 0)
            m_velocity.y = m_velocity.y / 2;
    }

    if (m_current_movement == E_RIGHT) {
        if (m_velocity.x > 0)
            m_velocity.x = m_velocity.x / 2;
    }
}


bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }

        if (TTF_Init() == -1) {
            printf("Error initializing SDL_Tff");
            return false;
        }

        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            //Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    gDotTexture.setRenderer(gRenderer);
    gBGTexture.setRenderer(gRenderer);
    gBGTextureValley.setRenderer(gRenderer);
    gMenu.setRenderer(gRenderer);
    gInfoMenuBar.setRenderer(gRenderer);
    gInfoMenuBarShadow.setRenderer(gRenderer);

    //Load dot texture
    if (!gDotTexture.loadFromFile("media/dot.bmp")) {
        printf("Failed to load dot texture!\n");
        getchar();
        success = false;
    }

    //Load background texture
    if (!gBGTexture.loadFromFile("media/ocean2.jpg")) {
        printf("Failed to load background texture!\n");
        getchar();
        success = false;
    }

    if (!gBGTextureValley.loadFromFile("media/valley.png")) {
        printf("Failed to load valley texture!\n");
        getchar();
        success = false;
    }

    Color color;
    color.randomize();

    if (!gInfoMenuBar.loadFromRenderedText("Teste", color.getSDLColor())) {
        printf("Failed to load text");
        getchar();
        success = false;
    }

    Color black;

    if (!gInfoMenuBarShadow.loadFromRenderedText("Teste", black.getSDLColor())) {
        printf("Failed to load text shadow");
        getchar();
        success = false;
    }

    if (!gMenu.loadFromFile("media/menuBar.png", 1)) {
        printf("Failed to load menubar9");
        getchar();
        success = false;
    }

    return success;
}

void close()
{
    //Free loaded images
    gDotTexture.free();
    gBGTexture.free();
    gBGTextureValley.free();
    gInfoMenuBar.free();
    gInfoMenuBarShadow.free();
    gMenu.free();

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *args[])
{
    srand(time(NULL));

    // Initialized to avoid error when calculating the last frame time and the game is pause
    Uint32 currentFrameTime = 0;
    Uint32 lastFrameTime = 0;
    double d_time;
    int fps = 40, fpsMill = 1000 / fps;
    SDL_Texture *backgroundText = NULL;
    char currentPath[FILENAME_MAX];

    //Start up SDL and create window
    if (!init()) printf("Failed to initialize!\n");

    else {
#ifdef _WIN32
		if (!GetCurrentDir(currentPath, sizeof(currentPath)))
			return errno;

		currentPath[sizeof(currentPath) - 1] = '\0'; /* not really required */
		#else
        ;
//		if (getcwd((char *)&currentPath, sizeof(currentPath)) == NULL)
//			cout << "Error while getting current dir" << endl;

#endif
        printf("The current working directory is %s\n", currentPath);

        //Load media
        if (!loadMedia())
            printf("Failed to load media!\n");

        else {
            //Event handler
            SDL_Event e;
            //Should be created just after TTF initialization done in init()
            Menu gameMenu = Menu();

            //The dot that will be moving around on the screen
            Dot dot;
            Dot target;
            Dot target2;
            Vector2d pos(dot.getPosX() + 400, dot.getPosY() + 200);
            target.setM_position(pos);
            target2.setM_position(pos);

            //The camera area
            SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
            lastFrameTime = 0;

            gBGTextureValley.setTransparency(100);

            int x, y;
            x = y = 100;

            // \todo Destroy this object
            Vector2d v(1,1);
            Vector2d t(x, y);
            dot.setM_velocity(v);
            target.setM_velocity(v);
            target2.setM_velocity(v);

            //FIXME
            //While application is running
            while (!quit) {
                currentFrameTime = SDL_GetTicks();
                d_time = (currentFrameTime - lastFrameTime) / 1000;
                lastFrameTime = SDL_GetTicks();
                /* FIXME Press Down, Up, and Enter in this order
                * The point will fall down*/
                //Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    //FIXME optimize performance using switch
                    //User requests quit
                    if (e.type == SDL_QUIT)
                        quit = true;

                    if (e.key.keysym.sym == SDLK_ESCAPE)
                        quit = true;

                    //Handle input for the dot
                    gameMenu.handleEvent(e);
                    dot.handleEvent(e);
                    if (e.key.keysym.sym == SDLK_p) {
                        // Check if there is any collectable object in range
                        if (dot.getCollectable(target)) {
                            target.setToRender(false);
                        }
                        else target.setToRender(true);
                    }

                    if (e.type == SDL_MOUSEMOTION) {
                        SDL_GetMouseState(&x, &y);
                    }
                }
                //Move the dot
                //dot.move();
                if (!isGamePaused) {
                    //Center the camera over the dot
                    camera.x = (dot.getPosX() + Dot::DOT_WIDTH / 2) - SCREEN_WIDTH / 2;
                    camera.y = (dot.getPosY() + Dot::DOT_HEIGHT / 2) - SCREEN_HEIGHT / 2;

                    //Keep the camera in bounds
                    if (camera.x < 0) {
                        camera.x = 0;
                    }
                    if (camera.y < 0) {
                        camera.y = 0;
                    }
                    if (camera.x > LEVEL_WIDTH - camera.w) {
                        camera.x = LEVEL_WIDTH - camera.w;
                    }
                    if (camera.y > LEVEL_HEIGHT - camera.h + MENU_HEIGHT) {
                        camera.y = LEVEL_HEIGHT - camera.h + MENU_HEIGHT;
                    }

                    //Clear screen
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(gRenderer);

                    //Render background
                    gBGTexture.render(0, 0, &camera);
                    gBGTextureValley.render(0, 0, &camera);

                    t.x = x;
                    t.y = y;

//                target.getSteering()->Seek(t);
                    dot.getSteering()->Flee(t);
//                target2.getSteering()->followLeader(target);

                    // \FIXME overriden by the steering bahaviour functions
                    dot.Update(d_time);
//                target.Update(d_time);
//                target2.Update(d_time);

                    //Render objects
                    // \FIXME dot.render(camera.x, camera.y) affects steering behaviour working
                    dot.render(0, 0);
//                target.render(0, 0);
//                target2.render(0, 0);

//                if (target.isToRender()) {
//                    target.render(0, 0);
//                }

                    //Update screen
                    SDL_RenderPresent(gRenderer);

                    SDL_Delay(fpsMill - d_time);
                }
                else {
                    SDL_RenderClear(gRenderer);
//                    gameMenu.adjustText();
                    //TODO find a better way to do this
                    Text* gameMainMenuOpt1 = gameMenu.getMainMenuOpt1();
                    Text* gameMainMenuOpt2 = gameMenu.getMainMenuOpt2();
                    Text* gameMainMenuOpt3 = gameMenu.getMainMenuOpt3();

                    gameMainMenuOpt1->surface = TTF_RenderText_Solid(gameMainMenuOpt1->font,
                            gameMainMenuOpt1->displayText.c_str(), gameMainMenuOpt1->color);
                    gameMainMenuOpt1->texture = SDL_CreateTextureFromSurface(gRenderer, gameMainMenuOpt1->surface);
                    SDL_RenderCopy(gRenderer, gameMainMenuOpt1->texture, NULL, &gameMainMenuOpt1->rect);

                    gameMainMenuOpt2->surface = TTF_RenderText_Solid(gameMainMenuOpt2->font,
                            gameMainMenuOpt2->displayText.c_str(), gameMainMenuOpt2->color);
                    gameMainMenuOpt2->texture = SDL_CreateTextureFromSurface(gRenderer, gameMainMenuOpt2->surface);
                    SDL_RenderCopy(gRenderer, gameMainMenuOpt2->texture, NULL, &gameMainMenuOpt2->rect);

                    gameMainMenuOpt3->surface = TTF_RenderText_Solid(gameMainMenuOpt3->font,
                            gameMainMenuOpt3->displayText.c_str(), gameMainMenuOpt3->color);
                    gameMainMenuOpt3->texture = SDL_CreateTextureFromSurface(gRenderer, gameMainMenuOpt3->surface);
                    SDL_RenderCopy(gRenderer, gameMainMenuOpt3->texture, NULL, &gameMainMenuOpt3->rect);
                    SDL_RenderPresent(gRenderer);
                }
            }
        }
    }
    //Free resources and close SDL
    close();

    return 0;
}

int Dot::getCollectable(Dot &obj)
{
    // \todo check screen boundaries -> really needed?
    // \todo should collectable be destroyed?
    if (!obj.IsCollectable()) return 0;

    bool isSameLine = obj.getPosX() <= this->getPosX() + 50 &&
            obj.getPosX() >= this->getPosX() - 50;
    bool isSameColumn = obj.getPosY() >= this->getPosY() - 10 &&
            obj.getPosY() <= this->getPosY() + 10;

    if (isSameLine && isSameColumn) {
        return 1;
    }
    return 0;
}
