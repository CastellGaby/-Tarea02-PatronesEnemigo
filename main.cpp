#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The surfaces
SDL_Surface *Backgrnd = NULL;
SDL_Surface *Meta = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *Personita[4];
SDL_Surface *En = NULL;
SDL_Surface *EnD= NULL;
SDL_Surface *EnT= NULL;



//The event structure
SDL_Event event;


//The color of the font
SDL_Color textColor = { 0, 0, 0 };

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );



    //Return the optimized surface
    return loadedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Tarea 02 Patrones Peronsajes-GACD", NULL );

    //If everything initialized fine
    return true;
}

bool load_files()
{
    Backgrnd = load_image("backgrounds.png");
    En = load_image("Enemigos/Enemigo01.png");
    EnD = load_image("Enemigos/Enemigo02.png");
    EnT=load_image("Enemigos/Enemigo04.png");

    Meta = load_image( "puerta.png" );


    //If there was a problem in loading the background
    if( Backgrnd == NULL )
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surfaces

    SDL_FreeSurface( Backgrnd );
    SDL_FreeSurface( screen );

    SDL_FreeSurface( Personita[0] );
    SDL_FreeSurface( Personita[1] );
    SDL_FreeSurface( Personita[2] );
    SDL_FreeSurface( Personita[3] );
    SDL_FreeSurface( En );
    SDL_FreeSurface( EnD);
    SDL_FreeSurface( EnT);

    //Quit SDL
    SDL_Quit();
}

int i = 0;

int main( int argc, char* args[] )
{
    int Perx = 0;
    int Pery = 0;
    int Enemx = 0;
    int Enemy = 200;
    bool EnemDer;
    bool EnemIzq;

    int EnDx = 300;
    int EnDy = 0;
    bool EnDDer;
    bool EnDIzq;

    int EnTx=0;
    int EnTy=400;
    int EnTDer;
    int EnTIzq;



    int pss=0;
    bool cont = true;

    //Quit flag
    bool quit = false;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }


    Personita[0] = load_image("Personita/Personita01.png");
    Personita[1] = load_image("Personita/Personita02.png");
    Personita[2] = load_image("Personita/Personita03.png");
    Personita[3] = load_image("Personita/Personita04.png");

    //While the user hasn't quit
    while(quit == false)
    {
         if(pss>3){
            pss=0;
        }
        //If there was a problem in loading the image
        if( Personita == NULL )
        {
            return 1;
        }


        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }
        apply_surface( 0, 0, Backgrnd, screen );
        apply_surface( 500 , 300 , Meta , screen );
        apply_surface(Perx,Pery,Personita[pss],screen);

        pss++;


        if(true){

            if(Enemx==0){
                EnemDer = true;
                EnemIzq = false;
            }

            if(Enemx == 522){
                EnemIzq = true;
                EnemDer = false;
            }

            if(EnemDer){
                apply_surface(Enemx,Enemy,En,screen);
                Enemx+=2;
            }

            if(EnemIzq){
                apply_surface(Enemx,Enemy,En,screen);
                Enemx-=2;
            }
        }

        if(true){
            if(EnDy ==0){
                EnDDer = false;
                EnDIzq = true;
            }

            if(EnDy == 416){
                EnDIzq = false;
                EnDDer = true;
            }

            if(EnDDer){
                apply_surface(EnDx,EnDy,EnD,screen);
                EnDy-=2;
            }

            if(EnDIzq){
                apply_surface(EnDx,EnDy,EnD,screen);
                EnDy+=2;
            }
        }

        if(true){

            if(EnTx==240){
                EnTDer = true;
                EnTIzq = false;
            }

            if(EnTx == 0){
                EnTIzq = true;
                EnTDer = false;
            }

            if(EnTDer){
                apply_surface(EnTx,EnTy,EnT,screen);
                EnTx-=2;
            }

            if(EnemIzq){
                apply_surface(EnTx,EnTy,EnT,screen);
                EnTx+=2;
            }
        }


        //Get the keystates
        Uint8 *keystates = SDL_GetKeyState( NULL );

        //If up is pressed
        if( keystates[ SDLK_UP ] )
        {
            if(Pery> 0)
            {
                Pery-=10;
            }
        }

        //If down is pressed
        if( keystates[ SDLK_DOWN ] )
        {
            if(Pery <= 416)
            {
                Pery+=10;
            }
        }

        //If left is pressed
        if( keystates[ SDLK_LEFT ] )
        {
            if(Perx  > 0)
            {
                Perx -=10;
            }
        }

        //If right is pressed
        if( keystates[ SDLK_RIGHT ] )
        {
            if(Perx  <= 576)
            {
                Perx +=10;
            }
        }

        if(true)
        {
            if((Perx+32)>= 576 && (Pery+32) >= 416)
            {
                exit(0);
            }
        }


        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

        SDL_Delay(50);

        if(pss > 3)
        {
            pss = 0;
        }
    }


    //Clean up
    clean_up();

    return 0;
}
