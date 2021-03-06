#pragma once

#include <string>
#include <vector>
#include <algorithm>

#include "BaseEntity.h"

#include "../Core/DCoordinates3.h"
#include "Core/Transformations.h"

using namespace std;
using namespace cagd;

namespace cor3d {

    enum Type{ROTATIONAL = 0, TRANSLATIONAL = 1};

    class Joint: public BaseEntity {
        friend ostream& operator <<(ostream& lhs, const Joint& rhs);
        friend istream& operator >>(istream& lhs, Joint& rhs);

        int                     _parent_id;
        vector<unsigned int>    _children_ids;
        Type                    _type;
        DCoordinate3            _axis;
        DCoordinate3            _orientation;
        DCoordinate3            _coordinate;
        DCoordinate3            _configuration;
        DCoordinate3            _scale;

    public:
        Joint(unsigned int id, string name, int parent_id, const DCoordinate3& parentCoordinate = DCoordinate3(0.0, 0.0, 0.0)): BaseEntity(id, name)
        {
            _parent_id  = parent_id;
            _type       = ROTATIONAL;
            _scale      = DCoordinate3(1, 1, 1);
            _orientation = DCoordinate3(0.0, 0.0, 0.0);
            _coordinate = DCoordinate3(parentCoordinate);
            _orientation = DCoordinate3(0.0, 0.0, 0.0);
        }

        void update_coordinates(const DCoordinate3& parent_coordinates);

        ///////////////////////////
        // getter methods        //
        ///////////////////////////
        int get_parent() const
        {
            return _parent_id;
        }

        vector<unsigned int> get_children() const
        {
            return _children_ids;
        }

        Type get_type() const
        {
            return _type;
        }

        const DCoordinate3& get_axis() const
        {
            return _axis;
        }

        const DCoordinate3& get_orientation() const
        {
            return _orientation;
        }

        double get_length() const
        {
            return 0;
        }

        const DCoordinate3& get_configuration() const
        {
            return _configuration;
        }

        const DCoordinate3& get_coordinates() const
        {
            return _coordinate;
        }

        const DCoordinate3& get_scale() const
        {
            return _scale;
        }

        static vector<BaseEntity> get_joint_types()
        {
            vector<BaseEntity> joint_types;
            joint_types.push_back(BaseEntity(ROTATIONAL, "ROTATIONAL"));
            joint_types.push_back(BaseEntity(TRANSLATIONAL, "TRANSLATIONAL"));
            return joint_types;
        }

        ///////////////////////////
        // setter methods        //
        ///////////////////////////
        void set_parent(int parent_id)
        {
            _parent_id = parent_id;
        }

        void add_child(unsigned int child_id)
        {
            _children_ids.push_back(child_id);
        }

        void remove_child(unsigned int child_id)
        {
            _children_ids.erase(std::remove(_children_ids.begin(), _children_ids.end(), child_id), _children_ids.end());
        }

        void set_type(Type type)
        {
            if (_type != type)
            {
                _type = type;
                _configuration = DCoordinate3(0, 0, 0);
            }
        }

        void set_axis(const DCoordinate3& axis)
        {
            _axis = axis;
        }

        void set_orientation(const DCoordinate3& orientation)
        {
            _orientation = orientation;
        }

        void set_coordinate(const DCoordinate3& coordinate)
        {
            _coordinate = coordinate;
        }

        void set_configuration(const DCoordinate3& configuration)
        {
            _configuration = configuration;
        }

        void set_scale(const DCoordinate3& scale)
        {
            _scale = scale;
        }
    };
}
