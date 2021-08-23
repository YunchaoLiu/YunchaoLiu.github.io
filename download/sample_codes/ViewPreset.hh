// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington UW TechTransfer, email: license@u.washington.edu.

#ifndef INCLUDED__INTERACTIVE_GUI_VIEW_PRESET_HH
#define INCLUDED__INTERACTIVE_GUI_VIEW_PRESET_HH

#include <interactive/gui/ViewPreset.fwd.hh>

#include <interactive/application/shared/ToolApplication.fwd.hh>
#include <interactive/application/shared/ViewOptionsWidget.fwd.hh>
#include <interactive/poseview/PoseGeom.hh>
#include <interactive/poseview/SideChainGeom.hh>
#include <interactive/util/Dictionary.hh>
#include <interactive/util/refcount/ReferenceCount.hh>





namespace interactive {
namespace gui {


///@brief A class that store and control all view option values
class ViewPreset: public interactive::util::ReferenceCount{
	static const char * SHOW_CLASHES                                      ;
	static const char * SHOW_EXPOSED                                      ;
	static const char * SHOW_VOIDS                                        ;
	static const char * SHOW_BACKBONE_ISSUES                              ;
	static const char * SHOW_BACKBONE_PINS                                ;
	static const char * SHOW_SHEET_HBONDS         	                      ;
	static const char * SHOW_HELIX_HBONDS         	                      ;
	static const char * SHOW_LOOP_HBONDS                                  ;
	static const char * SHOW_SIDECHAIN_HBONDS                             ;
	static const char * SHOW_NON_PROTEIN_HBONDS                           ;
	static const char * SHOW_BONDABLE_ATOMS                               ;
	static const char * SHOW_CONSTRAINTS          	                      ;
	static const char * SHOW_RESIDUE_BURIAL                               ;
	static const char * SHOW_ISOSURFACE                                   ;
	static const char * SYM_CHAIN_VISIBLE         	                      ;
	static const char * SYM_CHAIN_COLORS          	                      ;
	static const char * SHOW_MUTATED_RESIDUES     	                      ;
	static const char * SHOW_SIDECHAINS_WITH_ISSUES                       ;
	static const char * SHOW_OUTLINES             	                      ;
	static const char * DARK_BACKGROUND                                   ;
	static const char * WORKING_PULSE_STYLE       	                      ;
	static const char * SHOW_HYDROGENS                                    ;
	static const char * SIDECHAIN_MODE                                    ;


public:

    typedef enum {
    	BUILT_IN,
    	CUSTOMIZED
    }PresetType;

    typedef enum{
    	TRUE,
    	FALSE,
    	UNCHANGED
    }ViewOptionValue;


    ViewPreset(std::string preset_name);
    ~ViewPreset();


    const std::string & get_preset_name () const;
    void set_preset_name(std::string preset_name);

    const PresetType & get_preset_type() const;
    void set_preset_type(PresetType preset_type);

    void get_settings_from_dict(util::DictionaryOP preset_dict, std::string tag_prefix);

    void get_settings_from_app(application::shared::ToolApplicationAP app);

    void visualize_view_preset(application::shared::ToolApplicationAP app, Size selected_preset_index);

    void save_settings_to_dict(util::DictionaryOP preset_dict, std::string tag_prefix);

    void delete_settings_from_dict(util::DictionaryOP preset_dict, std::string tag_prefix);


private:

    std::string preset_name_;
    PresetType preset_type_;

    ViewOptionValue                            show_clashes_                                      ;
	ViewOptionValue                            show_exposed_                                      ;
	ViewOptionValue                            show_voids_                                        ;
	ViewOptionValue                            show_backbone_issues_                              ;
	ViewOptionValue                            show_backbone_pins_                                ;
	ViewOptionValue                            show_sheet_hbonds_                                 ;
	ViewOptionValue                            show_helix_hbonds_                                 ;
	ViewOptionValue                            show_loop_hbonds_                                  ;
	ViewOptionValue                            show_sidechain_hbonds_                             ;
	ViewOptionValue                            show_non_protein_hbonds_                           ;
	ViewOptionValue                            show_bondable_atoms_                               ;
	ViewOptionValue                            show_constraints_                                  ;
	ViewOptionValue                            show_residue_burial_                               ;
	ViewOptionValue                            show_isosurface_                                   ;
	ViewOptionValue                            sym_chain_visible_                                 ;
	ViewOptionValue                            sym_chain_colors_                                  ;
	ViewOptionValue                            show_mutated_residues_                             ;
	ViewOptionValue                            show_sidechains_with_issues_                       ;
	ViewOptionValue                            show_outlines_                                     ;
	ViewOptionValue                            dark_background_                                   ;
	ViewOptionValue                            working_pulse_style_                               ;
	poseview::ShowHydrogenType                 show_hydrogens_                                    ;
	poseview::SideChainGeom::ShowMode          sidechain_mode_                                    ;

	bool         bool_show_clashes_                    ;
	bool         bool_show_exposed_                    ;
	bool         bool_show_voids_                      ;
	bool         bool_show_backbone_issues_            ;
	bool         bool_show_backbone_pins_              ;
	bool         bool_show_sheet_hbonds_               ;
	bool         bool_show_helix_hbonds_               ;
	bool         bool_show_loop_hbonds_                ;
	bool         bool_show_sidechain_hbonds_           ;
	bool         bool_show_non_protein_hbonds_         ;
	bool         bool_show_bondable_atoms_             ;
	bool         bool_show_constraints_                ;
	bool         bool_show_residue_burials_            ;
	bool         bool_show_isosurface_                 ;
	bool         bool_sym_chain_visible_               ;
	bool         bool_sym_chain_colors_                ;
	bool         bool_show_mutated_residues_           ;
	bool         bool_show_sidechains_with_issues_     ;
	bool         bool_show_outlines_                   ;
	bool         bool_dark_background_                 ;
	bool         bool_working_pulse_style_             ;
	std::string  str_show_hydrogens_                   ;
	std::string  str_sidechain_mode_                   ;


	//a batch setter to set all ViewOptionValue given the bool value
	void bool2view_option_value_batch_setter();
	void view_option_value2boolbatch_setter();


    static void bool2view_option_value(const bool& in, ViewOptionValue & out);
    static void view_option_value2bool(const ViewOptionValue & in, bool & out);




};


} // namespace gui
} // namespace interactive

#endif // INCLUDED__INTERACTIVE_GUI_VIEW_PRESET_HH
