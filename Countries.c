//
// Created by itai and tomer.
//
#include "Countries.h"

struct st_GeographicArea{
    int topLeftX;
    int topLeftY;
    int bottomRightX;
    int bottomRightY;
};

struct st_City{
    char* name;
    char* knownFood;
    int numOfResidents;
};

struct st_Country{
    GeographicArea geoArea;
    char* name;
    int numberOfCities;
    City cities;
};


Country AddCountry (char* name, int x1, int y1, int x2, int y2) {
    if(name==NULL){
        return NULL;
    }
    Country newCountry = (Country) malloc(sizeof(struct st_Country));
    if (newCountry == NULL || x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0){
        return NULL;
    }
    if(x1==x2 && y1==2) { //if the points are actually the same point
        return NULL;
    }
    newCountry->name = (char*)malloc(sizeof(char)*strlen(name)+1);
    if (newCountry->name == NULL) {
        free(newCountry); // we free the entire country since his field "name" could not allocate memory in the heap
        return NULL;
    }
    strcpy(newCountry->name, name);
    newCountry->geoArea = (GeographicArea)malloc(sizeof(struct st_GeographicArea));
    if(newCountry->geoArea==NULL){
        free(newCountry->name);
        free(newCountry);
        return NULL;
    }
    newCountry->geoArea->topLeftX = x1;
    newCountry->geoArea->topLeftY = y1;
    newCountry->geoArea->bottomRightX = x2;
    newCountry->geoArea->bottomRightY = y2;
    newCountry->numberOfCities = 0;
    newCountry->cities = (City)malloc(0);
    return newCountry;
}
bool AddCityToCountry (Country country, City city){
    if(country==NULL || city==NULL){
        return false;
    }
    country->cities = (City)realloc(country->cities, sizeof(struct st_City)*(country->numberOfCities+1));
    if(country->cities == NULL) {
        free(city->name);
        free(city->knownFood);
        free(city);
        return false;
    }
    else{
        country->cities[country->numberOfCities].name = (char*)malloc(sizeof(char)*strlen(city->name)+1);
        if(country->cities[country->numberOfCities].name == NULL) { // if we couldn't allocate space for the city name we return NULL to main
            free(city->name);
            free(city->knownFood);
            free(city);
            return false;
        }
        country->cities[country->numberOfCities].knownFood = (char*)malloc(sizeof(char)*strlen(city->knownFood)+1);
        if(country->cities[country->numberOfCities].knownFood == NULL) { // if we couldn't allocate space for the city name we return NULL to main
            free(city->name);
            free(city->knownFood);
            free(city);
            return false;
        }
        //if we reached this line it means memory for both the city name and known-food had been allocated successfully and we can copy the strings from the city to our new city within the country
        strcpy(country->cities[country->numberOfCities].name, city->name);
        strcpy(country->cities[country->numberOfCities].knownFood, city->knownFood);
        country->cities[country->numberOfCities].numOfResidents = city->numOfResidents;
        country->numberOfCities++;
        free(city->name);
        free(city->knownFood);
        free(city);
        return true;
    }
}
status DeleteCityFromCountry (Country country, char* name){
    if(country==NULL || name==NULL){
        return failure;
    }
    for(int i=0; i < country->numberOfCities; i++){
        if(strcmp(country->cities[i].name, name) == 0){
            if(country->numberOfCities==1){ // if there is only one city within the country
                free(country->cities[i].name);
                free(country->cities[i].knownFood);
                free(country->cities);
                country->cities = (City)malloc(0);
                country->numberOfCities = 0;
                return success;
            }
            if(i!=country->numberOfCities-1){ //if the city isn't the last in the array, we copy the pointers to the last city's name and knownfood to the current city
                free(country->cities[i].name);
                country->cities[i].name = NULL;
                country->cities[i].name = country->cities[country->numberOfCities-1].name;
                if(country->cities[i].name == NULL) { // if we couldn't allocate space for the city name we return NULL
                    return failure;
                }
                free(country->cities[i].knownFood);
                country->cities[i].knownFood = NULL;
                country->cities[i].knownFood = country->cities[country->numberOfCities-1].knownFood;
                if(country->cities[i].knownFood == NULL) { // if we couldn't allocate space for the city name we return NULL to main
                    return failure;
                }
                country->cities[i].numOfResidents = country->cities[country->numberOfCities-1].numOfResidents;
            }
            else{
                free(country->cities[i].name);
                free(country->cities[i].knownFood);
            }
            country->cities = (City)realloc(country->cities, sizeof(struct st_City)*(country->numberOfCities-1));
            if(country->cities==NULL) {
                return failure;
            }
            country->numberOfCities--;
            return success;
        }
    }
    // if we reached this line it means there's no city in the country with the name of the city we want to delete
    return failure;
}
bool IsInArea (Country country, int x, int y){
    if (country->geoArea->bottomRightX<x||country->geoArea->topLeftX>x || country==NULL){
        return false;
    }
    if(country->geoArea->bottomRightY>y||country->geoArea->topLeftY<y){
        return false;
    }
    return true;
}
status FreeCountryMem(Element other){
    if(other==NULL){
        return failure;
    }
    Country country = (Country)other;
    for (int i=0;i<country->numberOfCities;i++) {
        free(country->cities[i].name);
        free(country->cities[i].knownFood);
    }
    free(country->cities);
    free(country->name);
    free(country->geoArea);
    free(country);
    return success;
}
Element DeepCopyCountry(Element other){
    if(other==NULL){
        return NULL;
    }
    Country country = (Country)other;
    Country newCountry = AddCountry(country->name, country->geoArea->topLeftX, country->geoArea->topLeftY,
                                    country->geoArea->bottomRightX, country->geoArea->bottomRightY);
    if(newCountry == NULL){
        return NULL;
    }
    newCountry->numberOfCities = country->numberOfCities;
    if(country->numberOfCities==0){
        newCountry->cities = realloc(newCountry->cities, sizeof(struct st_City));
    }
    else{
        newCountry->cities = realloc(newCountry->cities, sizeof(struct st_City)*country->numberOfCities);
    }
    if(newCountry->cities == NULL){
        free(newCountry->name);
        free(newCountry->geoArea);
        free(newCountry);
        return NULL;
    }
    for(int i = 0; i < newCountry->numberOfCities; i++){
        newCountry->cities[i].name = (char*)malloc(sizeof(char)*strlen(country->cities[i].name)+1);
        if(newCountry->cities[i].name == NULL){
            for(int j = 0; j < i; j++){
                free(newCountry->cities[i].name);
            }
            free(newCountry->cities);
            free(newCountry->geoArea);
            free(newCountry->name);
            free(newCountry);
            return NULL;
        }
        newCountry->cities[i].knownFood = (char*)malloc(sizeof(char)*strlen(country->cities[i].knownFood)+1);
        if(newCountry->cities[i].knownFood == NULL){
            for(int j = 0; j < i; j++){
                free(newCountry->cities[i].name);
                free(newCountry->cities[i].knownFood);
            }
            free(newCountry->cities);
            free(newCountry->name);
            free(newCountry);
            free(newCountry->geoArea);
            return NULL;
        }
        strcpy(newCountry->cities[i].name, country->cities[i].name);
        strcpy(newCountry->cities[i].knownFood, country->cities[i].knownFood);
        newCountry->cities[i].numOfResidents = country->cities[i].numOfResidents;
    }
    return (Element)newCountry;
}
status PrintCountry(Element other){
    if(other==NULL){
        return failure;
    }
    Country country = (Country)other;
    printf("Country %s ",country->name);
    printf("coordinates: <%d,%d> , <%d,%d>\n", country->geoArea->topLeftX, country->geoArea->topLeftY,
           country->geoArea->bottomRightX,country->geoArea->bottomRightY);
    for(int i=0;i<country->numberOfCities;i++){
        printf("\t %s includes %d residents and their favorite food is %s.\n",country->cities[i].name,
               country->cities[i].numOfResidents,country->cities[i].knownFood);
    }
    return success;
}

City CreateCity(char* name, char* food, int residentsNum){
    if(name==NULL || food==NULL){
        return NULL;
    }
    City newCity = (City) malloc(sizeof(struct st_Country));
    if(newCity == NULL){
        return NULL;
    }
    newCity->name = (char*) malloc(sizeof(char) * strlen(name) + 1);
    if(newCity->name == NULL){
        free(newCity);
        return NULL;
    }
    strcpy(newCity->name, name);
    newCity->knownFood = (char*) malloc((sizeof(char) * strlen(food) + 1));
    if(newCity->knownFood == NULL){
        free(newCity->name);
        free(newCity);
        return NULL;
    }
    strcpy(newCity->knownFood, food);
    newCity->numOfResidents = residentsNum;
    return newCity;
}

bool DoesCityExist(Country country, char* name){
    if(country==NULL || name==NULL){
        return false;
    }
    for(int i = 0 ; i<country->numberOfCities; i++) {
        if (strcmp(country->cities[i].name, name) == 0) {
            return true;
        }
    }
    return false;
}

Element CopyCountryName(Element name){
    if(name==NULL){
        return NULL;
    }
    char* countryName = (char*)malloc(sizeof(char)*strlen(name)+1);
    if(countryName==NULL){
        return NULL;
    }
    strcpy(countryName, (char*)name);
    return (Element)countryName;
}
//double check where this function should be
status DeleteCountryName(Element countryName){
    if(countryName == NULL) {
        return false;
    }
    free(countryName);
    return true;
}

status PrintCountryName(Element countryName){
    if(countryName==NULL){
        return failure;
    }
    printf("%s", (char*)countryName);
    return success;
}

bool AreCountryNamesEqual(Element firstName, Element secondName){
    if(firstName == NULL || secondName == NULL){
        return false;
    }
    if(strcmp((char*)firstName,(char*)secondName)!=0){
        return false;
    }
    return true;
}

int ChangeCountryNameToInteger(Element name){
    if(name==NULL){
        return -1; // to remember to check if its -1 whenever its called
    }
    char* countryName = (char*)name;
    int num;
    num = atoi(countryName);
    return num;
}

char* GetCountryName(Country country){
    if(country==NULL){
        return NULL;
    }
    char* temp = (char*) malloc(sizeof(char)*strlen(country->name)+1);
    if(temp==NULL){
        return NULL;
    }
    strcpy(temp, country->name);
    return temp;
}
