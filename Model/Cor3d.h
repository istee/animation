#pragma once

#include <string>
#include <vector>
#include <map>
#include <QObject>

#include "Skeleton.h"
#include "BaseEntityCollection.h"

using namespace std;

namespace cor3d {
    class Cor3d: public QObject, public BaseEntityCollection {
        Q_OBJECT

        vector<Skeleton*>   _skeletons;
        int                 _selected_skeleton_id;

        RenderingOptions*   _rendering_options;

    protected:
        vector<Skeleton*> get_data()
        {
            return _skeletons;
        }

    public:
        Cor3d();

        int get_skeleton_id_by_name(const string& name) const;
        string next_name() const;
        vector<BaseEntity*> get_skeleton_list();
        Skeleton* get_skeleton();
        Skeleton* getSkeletonById(unsigned int skeletonId);
        Skeleton* getSkeletonByName(const string& skeletonName);
        RenderingOptions* get_rendering_options();
        void importSkeleton(ifstream& stream);
        unsigned int get_selected_skeleton_id() const;
        RenderingOptions* getRenderingOpstions() const
        {
            return _rendering_options;
        }

    private:
        bool is_skeleton_id_valid(int skeleton_id);
        bool is_skeleton_selected();

    signals:
        void model_translation_changed(const DCoordinate3&);
        void model_rotation_changed(const DCoordinate3&);
        void model_zoom_changed(double zoom);

        void model_skeleton_added(const string& name);
        void model_skeleton_deleted(const string& name);
        void model_skeleton_renamed(const string& oldName, const string& newName);

        void model_skeleton_selection_changed(const string& oldSelectionName, const string& newSelectionName);
        void model_skeleton_name_changed();
        void model_skeleton_model_data_changed(const string& name);
        void model_skeleton_data_changed();
        void model_rendering_options_changed();

    public slots:
        void handle_view_translation_changed(const DCoordinate3&);
        void handle_view_rotation_changed(const DCoordinate3&);
        void handle_view_zoom_changed(double zoom);

        void handle_view_skeleton_added(string);
        void handle_view_skeleton_selected(int);
        void handle_view_skeleton_selected(const string&);
        void handle_view_skeleton_deleted(const string&);
        void handle_view_skeleton_exported(const string&);
        void handle_view_skeleton_renamed(const string&, const string&);
        void handle_view_skeleton_model_changed(const string&, const string&);
        void handle_view_skeleton_model_scale_changed(const string&, const DCoordinate3&);
        void handle_view_skeleton_model_offset_changed(const string&, const DCoordinate3&);

        void handle_view_skeleton_render_toggled(bool);
        void handle_view_skeleton_material_changed(int);
        void handle_view_joint_render_toggled(bool);
        void handle_view_joint_model_file_changed(const string&);
        void handle_view_joint_material_changed(int);
        void handle_view_selected_joint_material_changed(int);
        void handle_view_link_render_toggled(bool);
        void handle_view_link_model_file_changed(const string&);
        void handle_view_link_material_changed(int);

    };
}
