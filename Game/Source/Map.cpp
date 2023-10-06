
#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

#include <math.h>
#include "SDL_image/include/SDL_image.h"

Map::Map() : Module(), mapLoaded(false)
{
    name.Create("map");
}

// Destructor
Map::~Map()
{}

// Called before render is available
bool Map::Awake(pugi::xml_node config)
{
    LOG("Loading Map Parser");
    bool ret = true;

    return ret;
}

bool Map::Start() {

    //Calls the functon to load the map, make sure that the filename is assigned
    SString mapPath = path;
    mapPath += name;
    Load(mapPath);

    return true;
}

bool Map::Update(float dt)
{
    bool ret = true;

    if(mapLoaded == false)
        return false;

    // L05: TODO 6: Iterate all tilesets and draw all their 
    // images in 0,0 (you should have only one tileset for now)

    return ret;
}

// Called before quitting
bool Map::CleanUp()
{
    LOG("Unloading map");

    // L05: TODO 2: Make sure you clean up any memory allocated from tilesets/map


    return true;
}

// Load new map
bool Map::Load(SString mapFileName)
{
    bool ret = true;
    pugi::xml_document mapFileXML;

    // L05: TODO 3: Implement LoadMap to load the map properties
    // retrieve the paremeters of the <map> node and save it into map data

    pugi::xml_parse_result result = mapFileXML.load_file(mapFileName.GetString());
    if(result != NULL)
    {

    
    //Fill mapData variabl
    mapData.width = mapFileXML.child("map").attribute("width").as_int();
    mapData.height = mapFileXML.child("map").attribute("height").as_int();
    mapData.tileWidth = mapFileXML.child("map").attribute("tilewidth").as_int();
    mapData.tileHeight = mapFileXML.child("map").attribute("tileheight").as_int();
         
    // L05: TODO 4: Implement the LoadTileSet function to load the tileset properties
    //ret = false; // Remove this line when implementing the function
    

    //Iterate the Tileset
     for(pugi::xml_node tilesetNode = mapFileXML.child("map").child("tileset"); tilesetNode != NULL; tilesetNode = tilesetNode.next_sibling("tileset"))
     {
        TileSet* tileset = new TileSet();
        //Load Tileset attributes
        tileset->firstgid = tilesetNode.attribute("firstgid").as_int();
        tileset->name = tilesetNode.attribute("name").as_string();
        tileset->tileWidth = tilesetNode.attribute("tilewidth").as_int();
        tileset->tileHeight = tilesetNode.attribute("tileheight").as_int();
        tileset->spacing = tilesetNode.attribute("spacing").as_int();
        tileset->margin = tilesetNode.attribute("margin").as_int();
        tileset->tilecount = tilesetNode.attribute("tilecount").as_int();
        tileset->columns = tilesetNode.attribute("columns").as_int();
        //Load Tileset image
        SString textPath = path;
        path += tilesetNode.child("image").attribute("source").as_string();

        tileset->texture = app->tex->Load(textPath.GetString());
        //Load Tileset properties
        mapData.tilesets.Add(tileset);
     }

      

      
   
    // L05: TODO 5: LOG all the data loaded iterate all tilesetsand LOG everything
    if(ret == true)
    {
        LOG("Successfully parsed map XML file :%s", "");
        LOG("width : %d height : %d",0,0);
        LOG("tile_width : %d tile_height : %d",mapData.tileWidth,mapData.tileHeight);
        
        LOG("Tilesets----");

        ListItem<TileSet*>* tileset = mapData.tilesets.start;
        while(tileset != NULL){
            //iterate the tilesets
            LOG("name : %s firstgid : %d", tileset->data->name, tileset->data->firstgid);
            LOG("tile width : %d tile height : %d", tileset->data->tileWidth, tileset->data->tileHeight);
            LOG("spacing : %d margin : %d", tileset->data->spacing, tileset->data->margin);

            tileset = tileset->next;

        }
        
        
    }
    
    if(mapFileXML) mapFileXML.reset();
    else{
        LOG("Could not load map xml file %s. pugi error: %s", mapFileName.GetString(), result.description());
        ret = false;
    }
    }
    mapLoaded = ret;

    return ret;
}

