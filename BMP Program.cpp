#include "SDL/SDL.h"
#include <vector>
#include <string>
#include "SDL/SDL_ttf.h"

using namespace std;

SDL_Surface* pic = NULL;
SDL_Surface* updated = NULL;
SDL_Surface* screen = NULL;
SDL_Surface* file_to_open = NULL;
TTF_Font *font2 = NULL;
SDL_Color textColor = { 255, 255, 255 };
SDL_Event event;
SDL_Surface* text = NULL;

SDL_Surface *load_image( std::string filename ) 
{
    //Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;
    
    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
    
     //Load the image
    loadedImage = SDL_LoadBMP( filename.c_str() );
     //If nothing went wrong in loading the image
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );
        
        //Free the old image
        SDL_FreeSurface( loadedImage );
    }
    
    //If the image was optimized just fine
        if( optimizedImage != NULL )
        {
            //Map the color key
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 255, 0, 0 );
            
            //Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
        }
    //Return the optimized image
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;
    
    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;
    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}

void startSDL ()
{
      //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );
    TTF_Init();
    SDL_WM_SetCaption( "BMP Change Program", NULL );
    //Set up screen
    screen = SDL_SetVideoMode( 250, 200, 32, SDL_SWSURFACE );
    font2 = TTF_OpenFont( "arialbd.ttf", 14 );
    text = TTF_RenderText_Solid( font2, "What file do you want to open?", textColor );
}

void cleanup ()
{
         //Free the loaded image
    SDL_FreeSurface( pic );
    TTF_CloseFont( font2 );
    
    //Quit SDL_ttf
    TTF_Quit();
    //Quit SDL
    SDL_Quit();
}

vector <char> keyboard (vector <char> name)
{
   bool quit = false;
   for (;;)
    {
        for (;;)
        {
            SDL_WaitEvent (&event);
            if (event.type == SDL_KEYDOWN || event.type == SDL_QUIT)
               break;
        }
        if ( event.type == SDL_QUIT )
           break;
        else
            switch( event.key.keysym.sym )
            {
                    case SDLK_1: name.push_back ('1'); break;
                    case SDLK_2: name.push_back ('2'); break;
                    case SDLK_3: name.push_back ('3'); break;
                    case SDLK_4: name.push_back ('4'); break;
                    case SDLK_5: name.push_back ('5'); break;
                    case SDLK_6: name.push_back ('6'); break;
                    case SDLK_7: name.push_back ('7'); break;
                    case SDLK_8: name.push_back ('8'); break;
                    case SDLK_9: name.push_back ('9'); break;
                    case SDLK_0: name.push_back ('0'); break;
                    case SDLK_q: name.push_back ('q'); break;
                    case SDLK_w: name.push_back ('w'); break;
                    case SDLK_e: name.push_back ('e'); break;
                    case SDLK_r: name.push_back ('r'); break;
                    case SDLK_t: name.push_back ('t'); break;
                    case SDLK_y: name.push_back ('y'); break;
                    case SDLK_u: name.push_back ('u'); break;
                    case SDLK_i: name.push_back ('i'); break;
                    case SDLK_o: name.push_back ('o'); break;
                    case SDLK_p: name.push_back ('p'); break;
                    case SDLK_a: name.push_back ('a'); break;
                    case SDLK_s: name.push_back ('s'); break;
                    case SDLK_d: name.push_back ('d'); break;
                    case SDLK_f: name.push_back ('f'); break;
                    case SDLK_g: name.push_back ('g'); break;
                    case SDLK_h: name.push_back ('h'); break;
                    case SDLK_j: name.push_back ('j'); break;
                    case SDLK_k: name.push_back ('k'); break;
                    case SDLK_l: name.push_back ('l'); break;
                    case SDLK_z: name.push_back ('z'); break;
                    case SDLK_x: name.push_back ('x'); break;
                    case SDLK_c: name.push_back ('c'); break;
                    case SDLK_v: name.push_back ('v'); break;
                    case SDLK_b: name.push_back ('b'); break;
                    case SDLK_n: name.push_back ('n'); break;
                    case SDLK_m: name.push_back ('m'); break;
                    case SDLK_PERIOD: name.push_back ('.'); break;
                    case SDLK_KP1: name.push_back ('1'); break;
                    case SDLK_KP2: name.push_back ('2'); break;
                    case SDLK_KP3: name.push_back ('3'); break;
                    case SDLK_KP4: name.push_back ('4'); break;
                    case SDLK_KP5: name.push_back ('5'); break;
                    case SDLK_KP6: name.push_back ('6'); break;
                    case SDLK_KP7: name.push_back ('7'); break;
                    case SDLK_KP8: name.push_back ('8'); break;
                    case SDLK_KP9: name.push_back ('9'); break;
                    case SDLK_KP0: name.push_back ('0'); break;
                    case SDLK_BACKSPACE: name.pop_back (); break;
                    case SDLK_RETURN: quit = true; break;
            }
        if (quit)
           break;
        string temp;
        for (int i = 0; i < name.size();i++)
            temp += name[i];
        file_to_open = TTF_RenderText_Solid(font2, temp.c_str(), textColor);
       // apply_surface (-1,-1,background,screen);
        apply_surface ( 10, 30, text, screen);
        apply_surface ( 10, 100, file_to_open, screen );
        SDL_Flip ( screen );
    }
    return name;
}

Uint32 get_pixel32( SDL_Surface *surface, int x, int y )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Get the requested pixel
    return pixels[ ( y * surface->w ) + x ];
}

void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Set the pixel
    pixels[ ( y * surface->w ) + x ] = pixel;
}

SDL_Surface *invert_colours( SDL_Surface *surface )
{
    //Pointer to the soon to be flipped surface
    SDL_Surface *inverse = NULL;
    
    //If the image is color keyed
    if( SDL_SRCCOLORKEY )
    {
        inverse = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, 0 );
    }
    //Otherwise
    else
    {
        inverse = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask );
    }

    //If the surface must be locked
    if( SDL_MUSTLOCK( surface ) )
    {
        //Lock the surface
        SDL_LockSurface( surface );
    }

    //Go through columns
    for( int x = 0; x < inverse->w; x++)
    {
        //Go through rows
        for( int y = 0; y < inverse->h; y++)
        {
             Uint8 r,g,b;
             //Get pixel
            Uint32 pixel = get_pixel32( surface, x, y );
            SDL_GetRGB (pixel, surface->format, &r, &g, &b);
            r = (Uint8)255 - r;
            g = (Uint8)255 - g;
            b = (Uint8)255 - b;
            pixel = r;
            pixel = pixel*256 + g;
            pixel = pixel*256 + b;
            //Copy pixel
            put_pixel32( inverse, x, y, pixel );
        }    
    }
    
    //Unlock surface
    if( SDL_MUSTLOCK( surface ) )
    {
        SDL_UnlockSurface( surface );
    }
    
    //Copy color key
    if( surface->flags & SDL_SRCCOLORKEY )
    {
        SDL_SetColorKey( inverse, SDL_RLEACCEL | SDL_SRCCOLORKEY, surface->format->colorkey );
    }
	
    //Return flipped surface
    return inverse;
}

SDL_Surface *greyscale( SDL_Surface *surface )
{
    //Pointer to the soon to be flipped surface
    SDL_Surface *grey = NULL;
    
    //If the image is color keyed
    if( SDL_SRCCOLORKEY )
    {
        grey = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, 0 );
    }
    //Otherwise
    else
    {
        grey = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask );
    }

    //If the surface must be locked
    if( SDL_MUSTLOCK( surface ) )
    {
        //Lock the surface
        SDL_LockSurface( surface );
    }

    //Go through columns
    for( int x = 0; x < grey->w; x++)
    {
        //Go through rows
        for( int y = 0; y < grey->h; y++)
        {
             Uint8 r,g,b;
             //Get pixel
            Uint32 pixel = get_pixel32( surface, x, y );
            SDL_GetRGB (pixel, surface->format, &r, &g, &b);
            r = (r+b+g)/3;
            g = r;
            b = r;
            pixel = r;
            pixel = pixel*256 + g;
            pixel = pixel*256 + b;
            //Copy pixel
            put_pixel32( grey, x, y, pixel );
        }    
    }
    
    //Unlock surface
    if( SDL_MUSTLOCK( surface ) )
    {
        SDL_UnlockSurface( surface );
    }
    
    //Copy color key
    if( surface->flags & SDL_SRCCOLORKEY )
    {
        SDL_SetColorKey( grey, SDL_RLEACCEL | SDL_SRCCOLORKEY, surface->format->colorkey );
    }
	
    //Return flipped surface
    return grey;
}

SDL_Surface *double_size( SDL_Surface *surface )
{
    //Pointer to the soon to be flipped surface
    SDL_Surface *doubles = NULL;
    
    //If the image is color keyed
    if( SDL_SRCCOLORKEY )
    {
        doubles = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w*2, surface->h*2, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, 0 );
    }
    //Otherwise
    else
    {
        doubles = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w*2, surface->h*2, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask );
    }

    //If the surface must be locked
    if( SDL_MUSTLOCK( surface ) )
    {
        //Lock the surface
        SDL_LockSurface( surface );
    }

    //Go through columns
    for( int x = 0; x < doubles->w; x++)
    {
        //Go through rows
        for( int y = 0; y < doubles->h; y++)
        {
             Uint8 r,g,b;
             //Get pixel
            Uint32 pixel = get_pixel32( surface, x/2, y/2 );
            SDL_GetRGB (pixel, surface->format, &r, &g, &b);
          /*  r = (Uint8)255 - r;
            g = (Uint8)255 - g;
            b = (Uint8)255 - b;
            pixel = r;
            pixel = pixel*256 + g;
            pixel = pixel*256 + b;*/
            //Copy pixel
            put_pixel32( doubles, x, y, pixel );
        }    
    }
    
    //Unlock surface
    if( SDL_MUSTLOCK( surface ) )
    {
        SDL_UnlockSurface( surface );
    }
    
    //Copy color key
    if( surface->flags & SDL_SRCCOLORKEY )
    {
        SDL_SetColorKey( doubles, SDL_RLEACCEL | SDL_SRCCOLORKEY, surface->format->colorkey );
    }
	
    //Return flipped surface
    return doubles;
}

int main ( int argc, char* args[] )
{
    startSDL();
    vector <char> file;
    apply_surface ( 10, 30, text, screen);
    SDL_Flip ( screen );
    file = keyboard (file);
    string file2 = "", file3 = "modified pics/";
    for (int i = 0; i < file.size(); i++)
    {
        file2 += file [i];
    }
    for (int i = 0; i < file.size()-4; i++)
    {
        file3 += file [i];
    }
    file3+="_modified.bmp";
    pic = load_image ( file2.c_str() );
   // apply_surface (0,0,pic,screen);
    SDL_Surface* updated = NULL;    
    updated = invert_colours( pic );  
  //  apply_surface (250,0,updated,screen);  
    SDL_SaveBMP (updated, file3.c_str());
    file3 = "modified pics/";
    for (int i = 0; i < file.size()-4; i++)
    {
        file3 += file [i];
    }
    file3+="_greyscale.bmp";
    updated = greyscale( pic );  
    SDL_SaveBMP (updated, file3.c_str());
    file3 = "modified pics/";
    for (int i = 0; i < file.size()-4; i++)
    {
        file3 += file [i];
    }
    file3+="_doublesize.bmp";
    updated = double_size( pic );  
    SDL_SaveBMP (updated, file3.c_str());
    
   // SDL_Flip ( screen );
/*    for (;;)
        {
            SDL_WaitEvent (&event);
            if (event.type == SDL_KEYDOWN || event.type == SDL_QUIT)
               break;
        }*/
    cleanup();
    
    return 0;
}

