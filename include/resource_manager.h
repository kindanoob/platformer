#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include<map>


template<typename Enum, typename Resource>
class Resource_manager {
public:
    std::map<Enum, Resource> resource_map;
    Resource& get_resource(Enum name) {
        return resource_map[name];
    };
protected:
    void add_resource(Enum name, const std::string &filename) {
        Resource res;
        res.loadFromFile(filename);
        resource_map.insert(std::make_pair(name, res));
    };
private:
};


#endif // RESOURCE_MANAGER_H_
