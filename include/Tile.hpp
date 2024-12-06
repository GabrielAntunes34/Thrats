#ifndef TILE_H
#define TILE_H

class Tile {
    private:
        int id;
        bool tangibility;
        // float pathfinding???

    public:
        Tile(int id = -1, bool tangibility = false)
        : id(id), tangibility(tangibility) {};

        // Getters
        int getId();
        bool isTangible();

        // Setters
        void setTaniblity(bool tangibility);
        void setId(int id);

        // Mechanics
        // CalculatePath???
};

#endif