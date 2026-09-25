#ifndef CONTAINER_H
#define CONTAINER_H


#include <vector>
#include "shape.h"

class Container
{
public:
    Container();
    ~Container(){
        clear();
    }

    void add(Shape * shape) {
        shapes_.push_back(shape);
    }

    Shape * getObject(int index){
        return shapes_[index];
    }

    int getCount() const {
        return shapes_.size();
    }

    void removeAt(int index){
        delete shapes_[index];
        shapes_.erase(shapes_.begin() + index);
    }

    void clear() {
        for (int i = 0; i < shapes_.size(); ++i) {
            delete shapes_[i];
        }
        shapes_.clear();
    }

    std::vector<Shape*> getSelectedShapes() const {
        std::vector<Shape*> selected;
        for (Shape* shape : shapes_) {
            if (shape->isSelected()) {
                selected.push_back(shape);
            }
        }
        return selected;
    }

    void clearSelection() {
        for (Shape* shape : shapes_) {
            shape->setSelected(false);
        }
    }

private:
    std::vector<Shape*> shapes_;
    int currentIndex_;
};

#endif // CONTAINER_H
