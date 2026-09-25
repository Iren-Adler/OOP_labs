#ifndef CONTAINER_H
#define CONTAINER_H


#include <vector>
#include "circle.h"

class Container
{
public:
    Container();
    ~Container(){
        for (int i = 0; i < circles_.size(); ++i) {
            delete circles_[i];
        }
    }

    void add(Circle* circle) {
        circles_.push_back(circle);
    }

    Circle* getObject(int index){
        return circles_[index];
    }

    int getCount() const {
        return circles_.size();
    }
    void removeAt(int index){
        delete circles_[index];
        circles_.erase(circles_.begin() + index);
    }

    void clear() {
        for (int i = 0; i < circles_.size(); ++i) {
            delete circles_[i];
        }
        circles_.clear();
    }


private:
    std::vector<Circle*> circles_;
    int currentIndex_;
};

#endif // CONTAINER_H
