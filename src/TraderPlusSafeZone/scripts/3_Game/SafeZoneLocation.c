class SafeZoneLocation
{   
    int id; // This is Zone ID.
    bool isActive; // this value is used to determine if the zone is active or not.
    string name; // This is Zone Name of the safe zone.
    vector position; // This is Zone Position.
    int radius; // This is Zone Radius of the safe zone.
    bool isEntitiesCleanActive = true; // When active the zone is cleaned from all aniamls and zombies, besides the once located in the allowedAnimals array.
    ref array<string> allowedAnimals; // Array containing the names of the animals that are allowed in the safe zone when clean up is active.


    void SafeZoneLocation(bool isActive, int id, string name, vector position, int radius, bool isEntitiesCleanActive, array<string> allowedAnimals)
    {
        this.isActive = isActive;
        this.id = id;
        this.name = name;
        this.position = position;
        this.radius = radius;
        this.isEntitiesCleanActive = true;
        this.allowedAnimals = new array<string>();
    }
}