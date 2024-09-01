class SafeZoneLocation
{   
    int id;
    // this value can deactivate the safezone
    bool isActive;
    string name;
    vector position;
    int radius;

    void SafeZoneLocation(bool isActive,int id, string name, vector position, int radius)
    {
        this.isActive = isActive;
        this.id = id;
        this.name = name;
        this.position = position;
        this.radius = radius;
    }
}