#pragma once

#include "IMainWindowTab.h"

#include "ui_PostureEditorTab.h"

class PostureEditorTab: public IMainWindowTab, public Ui::PostureEditorTab
{
    Q_OBJECT
public:
    PostureEditorTab(QWidget* parent = 0);
    void initialize();

    //inherited slots
    void skeleton_list_changed();
    void skeleton_selected();
    void selected_skeleton_name_changed();
    void selected_skeleton_data_changed();
    void selected_skeleton_joint_list_changed();
    void selected_skeleton_joint_selected_changed();
    void selected_skeleton_joint_name_changed();
    void selected_skeleton_joint_data_changed();
    void selected_skeleton_joint_selection_changed();
    void transformations_changed();
    void rendering_options_changed();

public slots:
    void handle_model_skeleton_selection_changed();

private slots:
//    void skeleton_added(const string& name);
//    void skeleton_selected(int);
//    void skeleton_deleted(int id);

//    void skeleton_name_edited(int skeleton_id, const string& name);
//    void skeleton_model_file_edited(int skeleton_id, const string& file);
//    void skeleton_model_scale_edited(int skeleton_id, const DCoordinate3& model_scale);
//    void skeleton_model_offset_edited(int skeleton_id, const DCoordinate3& model_offset);

//    void joint_added(int skeleton_id, const string& name, int parent_id);
//    void joint_selected(int skeleton_id, int joint_id);

//    void joint_parent_edited(int skeleton_id, int joint_id, int parent_id);
//    void joint_type_edited(int skeleton_id, int joint_id, Type type);
//    void joint_axis_edited(int skeleton_id, int joint_id, const DCoordinate3& axis);
//    void joint_orientation_edited(int skeleton_id, int joint_id, const DCoordinate3& orientation);
//    void joint_configuration_edited(int skeleton_id, int joint_id, const DCoordinate3& configuration);

//    void rendering_options_edited(RenderingOptions* rendering_options);
};
