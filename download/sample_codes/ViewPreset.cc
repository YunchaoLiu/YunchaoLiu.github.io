// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington UW TechTransfer, email: license@u.washington.edu.

#include <interactive/gui/ViewPreset.hh>

#include <interactive/application/appposeview/ContactMapComposite.hh>
#include <interactive/application/appposeview/HBondComposite.hh>
#include <interactive/application/appposeview/HydrophobicComposite.hh>
#include <interactive/application/appposeview/IdealityComposite.hh>
#include <interactive/application/appposeview/FoldTreeComposite.hh>
#include <interactive/application/appposeview/ReferencePoseInfoGeom.hh>
#include <interactive/application/appposeview/ResidueBurialComposite.hh>
#include <interactive/application/appposeview/VoidGeom.hh>
#include <interactive/application/shared/ToolApplication.hh>
#include <interactive/application/shared/ViewOptionsWidget.hh>
#include <interactive/geom/Viewport.hh>
#include <interactive/gui/CheckBox.hh>
#include <interactive/gui/dialogs.hh>
#include <interactive/gui/SelectionList.hh>
#include <interactive/gui/TopLevel.hh>
#include <interactive/poseview/ConstraintSetComposite.hh>
#include <interactive/poseview/PairEnergyComposite.hh>
#include <interactive/poseview/PoseGeom.hh>
#include <interactive/poseview/SideChainGeom.hh>
#include <interactive/translate/Translator.hh>
#include <interactive/util/options_dict.hh>
#include <interactive/util/path.hh>
#include <interactive/util/resources.hh>
#include <boost/algorithm/string.hpp>
#include <utility/file/FileName.hh>

namespace interactive {
namespace gui {

const char * ViewPreset::SHOW_CLASHES                                      = "show_clashes";
const char * ViewPreset::SHOW_EXPOSED                                      = "show_exposed";
const char * ViewPreset::SHOW_VOIDS                                        = "show_voids";
const char * ViewPreset::SHOW_BACKBONE_ISSUES                              = "show_backbone_issues";
const char * ViewPreset::SHOW_BACKBONE_PINS                                = "show_backbone_pins";
const char * ViewPreset::SHOW_SHEET_HBONDS         	                       = "show_sheet_hbonds";
const char * ViewPreset::SHOW_HELIX_HBONDS         	                       = "show_helix_hbonds";
const char * ViewPreset::SHOW_LOOP_HBONDS                                  = "show_loop_hbonds";
const char * ViewPreset::SHOW_SIDECHAIN_HBONDS                             = "show_sidechain_hbonds";
const char * ViewPreset::SHOW_NON_PROTEIN_HBONDS                           = "show_non_protein_hbonds";
const char * ViewPreset::SHOW_BONDABLE_ATOMS                               = "show_bondable_atoms";
const char * ViewPreset::SHOW_CONSTRAINTS          	                       = "show_constraints";
const char * ViewPreset::SHOW_RESIDUE_BURIAL                               = "show_residue_burial";
const char * ViewPreset::SHOW_ISOSURFACE                                   = "show_isosurface";
const char * ViewPreset::SYM_CHAIN_VISIBLE         	                       = "sym_chain_visible";
const char * ViewPreset::SYM_CHAIN_COLORS          	                       = "sym_chain_colors";
const char * ViewPreset::SHOW_MUTATED_RESIDUES     	                       = "show_mutated_residues";
const char * ViewPreset::SHOW_SIDECHAINS_WITH_ISSUES                       = "show_sidechains_with_issues";
const char * ViewPreset::SHOW_OUTLINES             	                       = "show_outlines";
const char * ViewPreset::DARK_BACKGROUND                                   = "dark_background";
const char * ViewPreset::WORKING_PULSE_STYLE       	                       = "working_pulse_style";
const char * ViewPreset::SHOW_HYDROGENS                                    = "show_hydrogens";
const char * ViewPreset::SIDECHAIN_MODE                                    = "sidechain_mode";



ViewPreset::ViewPreset(std::string preset_name) {
	preset_name_ = preset_name;

	show_clashes_                                       = ViewPreset::UNCHANGED;
	show_exposed_                                       = ViewPreset::UNCHANGED;
	show_voids_                                         = ViewPreset::UNCHANGED;
	show_backbone_issues_                               = ViewPreset::UNCHANGED;
	show_backbone_pins_                                 = ViewPreset::UNCHANGED;
	show_sheet_hbonds_                                  = ViewPreset::UNCHANGED;
	show_helix_hbonds_                                  = ViewPreset::UNCHANGED;
	show_loop_hbonds_                                   = ViewPreset::UNCHANGED;
	show_sidechain_hbonds_                              = ViewPreset::UNCHANGED;
	show_non_protein_hbonds_                            = ViewPreset::UNCHANGED;
	show_bondable_atoms_                                = ViewPreset::UNCHANGED;
	show_constraints_                                   = ViewPreset::UNCHANGED;
	show_residue_burial_                                = ViewPreset::UNCHANGED;
	show_isosurface_                                    = ViewPreset::UNCHANGED;
	sym_chain_visible_                                  = ViewPreset::UNCHANGED;
	sym_chain_colors_                                   = ViewPreset::UNCHANGED;
	show_mutated_residues_                              = ViewPreset::UNCHANGED;
	show_sidechains_with_issues_                        = ViewPreset::UNCHANGED;
	show_outlines_                                      = ViewPreset::UNCHANGED;
	dark_background_                                    = ViewPreset::UNCHANGED;
	working_pulse_style_                                = ViewPreset::UNCHANGED;
	show_hydrogens_                                     = poseview::ShowHydrogenType::HY_NONE	;
	sidechain_mode_                                     = poseview::SideChainGeom::ShowMode::SHOW_NOTHING;
};

ViewPreset::~ViewPreset() {

};

const std::string &
ViewPreset::get_preset_name() const {
	return preset_name_;
};

void
ViewPreset::set_preset_name(std::string preset_name) {
	preset_name_ = preset_name;
};

const
ViewPreset::PresetType &
ViewPreset::get_preset_type() const {
	return preset_type_;
};

void
ViewPreset::set_preset_type(PresetType preset_type) {
	preset_type_ = preset_type;
};


void
ViewPreset::get_settings_from_dict(util::DictionaryOP preset_dict, std::string tag_prefix){

	preset_dict->get(tag_prefix + SHOW_CLASHES                      ,bool_show_clashes_               );
	preset_dict->get(tag_prefix + SHOW_EXPOSED                      ,bool_show_exposed_               );
	preset_dict->get(tag_prefix + SHOW_VOIDS                        ,bool_show_voids_                 );
	preset_dict->get(tag_prefix + SHOW_BACKBONE_ISSUES              ,bool_show_backbone_issues_       );
	preset_dict->get(tag_prefix + SHOW_BACKBONE_PINS                ,bool_show_backbone_pins_         );
	preset_dict->get(tag_prefix + SHOW_SHEET_HBONDS         	    ,bool_show_sheet_hbonds_          );
	preset_dict->get(tag_prefix + SHOW_HELIX_HBONDS         	    ,bool_show_helix_hbonds_          );
	preset_dict->get(tag_prefix + SHOW_LOOP_HBONDS                  ,bool_show_loop_hbonds_           );
	preset_dict->get(tag_prefix + SHOW_SIDECHAIN_HBONDS             ,bool_show_sidechain_hbonds_      );
	preset_dict->get(tag_prefix + SHOW_NON_PROTEIN_HBONDS           ,bool_show_non_protein_hbonds_    );
	preset_dict->get(tag_prefix + SHOW_BONDABLE_ATOMS               ,bool_show_bondable_atoms_        );
	preset_dict->get(tag_prefix + SHOW_CONSTRAINTS          	    ,bool_show_constraints_           );
	preset_dict->get(tag_prefix + SHOW_RESIDUE_BURIAL               ,bool_show_residue_burials_       );
	preset_dict->get(tag_prefix + SHOW_ISOSURFACE                   ,bool_show_isosurface_            );
	preset_dict->get(tag_prefix + SYM_CHAIN_VISIBLE         	    ,bool_sym_chain_visible_          );
	preset_dict->get(tag_prefix + SYM_CHAIN_COLORS          	    ,bool_sym_chain_colors_           );
	preset_dict->get(tag_prefix + SHOW_MUTATED_RESIDUES     	    ,bool_show_mutated_residues_      );
	preset_dict->get(tag_prefix + SHOW_SIDECHAINS_WITH_ISSUES       ,bool_show_sidechains_with_issues_);
	preset_dict->get(tag_prefix + SHOW_OUTLINES             	    ,bool_show_outlines_              );
	preset_dict->get(tag_prefix + DARK_BACKGROUND                   ,bool_dark_background_            );
	preset_dict->get(tag_prefix + WORKING_PULSE_STYLE       	    ,bool_working_pulse_style_        );
	preset_dict->get(tag_prefix + SHOW_HYDROGENS                    ,str_show_hydrogens_              );
	preset_dict->get(tag_prefix + SIDECHAIN_MODE                    ,str_sidechain_mode_              );

	bool2view_option_value_batch_setter();

	//hydrogen selection list
	int show_hydrogens_index = std::find(poseview::SHOW_HYDROGEN_NAMES, poseview::SHOW_HYDROGEN_NAMES + poseview::NUM_SHOW_HYDROGENS, str_show_hydrogens_) - poseview::SHOW_HYDROGEN_NAMES; // subtract SHOW_HYDROGEN_NAMES array to typecast the std::find() iterator as an int

	poseview::ShowHydrogenType show_hydrogens = poseview::HY_NONE;
	if (show_hydrogens_index != poseview::NUM_SHOW_HYDROGENS) {
		show_hydrogens = poseview::ShowHydrogenType(show_hydrogens_index);
	}
	show_hydrogens_ = show_hydrogens;

	//sidechain selection list
	int side_chain_index = std::find(poseview::SideChainGeom::SHOW_MODE_NAMES, poseview::SideChainGeom::SHOW_MODE_NAMES + poseview::SideChainGeom::NUM_SHOW_MODES, str_sidechain_mode_) - poseview::SideChainGeom::SHOW_MODE_NAMES;

	poseview::SideChainGeom::ShowMode show_mode = poseview::SideChainGeom::SHOW_NOTHING;
	if (side_chain_index != poseview::SideChainGeom::NUM_SHOW_MODES) {
		show_mode = poseview::SideChainGeom::ShowMode(side_chain_index);
	}
	sidechain_mode_ = show_mode;

};

void
ViewPreset::get_settings_from_app(application::shared::ToolApplicationAP app){

	bool_show_clashes_                = app->get_show_clashes();
	bool_show_exposed_                = app->get_show_exposed();
    bool_show_voids_                  = app->get_show_voids();
    bool_show_backbone_issues_        = app->get_show_backbone_issues();
    bool_show_backbone_pins_          = app->get_show_backbone_pins();
    bool_show_sheet_hbonds_           = app->get_show_sheet_hbonds();
    bool_show_helix_hbonds_           = app->get_show_helix_hbonds();
    bool_show_loop_hbonds_            = app->get_show_loop_hbonds();
    bool_show_sidechain_hbonds_       = app->get_show_sidechain_hbonds();
    bool_show_non_protein_hbonds_     = app->get_show_non_protein_hbonds();
    bool_show_bondable_atoms_         = app->get_show_bondable_atoms();
    bool_show_constraints_            = app->get_show_constraints();
    bool_show_residue_burials_        = app->get_show_residue_burial();
    bool_show_isosurface_             = app->get_show_isosurface();
    bool_sym_chain_visible_           = app->get_sym_chain_visible();
    bool_sym_chain_colors_            = app->get_sym_chain_colors();
    bool_show_mutated_residues_       = app->get_color_mutated_residues();
    bool_show_sidechains_with_issues_ = app->get_show_sidechains_with_issues();
    bool_show_outlines_               = app->get_show_outlines();
    bool_dark_background_             = app->get_dark_background();
    bool_working_pulse_style_         = app->get_working_pulse_style();

    bool2view_option_value_batch_setter();

    show_hydrogens_                   = app->get_show_hydrogens();
    sidechain_mode_                   = app->get_side_chain_mode();


};

void
ViewPreset::visualize_view_preset(application::shared::ToolApplicationAP app, Size selected_preset_index){
//	using namespace poseview;


	view_option_value2boolbatch_setter();


	//===change the checkbox and selectionlist
	app->set_show_clashes_without_view_change                                 (bool_show_clashes_                );
	app->set_show_exposed_without_view_change                                 (bool_show_exposed_                );
	app->set_show_voids_without_view_change                                   (bool_show_voids_                  );
	app->set_show_backbone_issues_without_view_change                         (bool_show_backbone_issues_        );
	app->set_show_backbone_pins_without_view_change                           (bool_show_backbone_pins_          );
	app->set_show_sheet_hbonds_without_view_change                            (bool_show_sheet_hbonds_           );
	app->set_show_helix_hbonds_without_view_change                            (bool_show_helix_hbonds_           );
	app->set_show_loop_hbonds_without_view_change                             (bool_show_loop_hbonds_            );
	app->set_show_sidechain_hbonds_without_view_change                        (bool_show_sidechain_hbonds_       );
	app->set_show_non_protein_hbonds_without_view_change                      (bool_show_non_protein_hbonds_     );
	app->set_show_bondable_atoms_without_view_change                          (bool_show_bondable_atoms_         );
	app->set_show_constraints_without_view_change                             (bool_show_constraints_            );
	app->set_show_residue_burial_without_view_change                          (bool_show_residue_burials_        );
	app->set_show_isosurface_without_view_change                              (bool_show_isosurface_             );
	app->set_show_sym_chains_without_view_change                              (bool_sym_chain_visible_           );
	app->set_show_sym_chain_colors_without_view_change                        (bool_sym_chain_colors_            );
	app->set_show_mutated_residues_without_view_change                        (bool_show_mutated_residues_       );
	app->set_show_sidechains_with_issues_without_view_change                  (bool_show_sidechains_with_issues_ );
	app->set_show_outlines_without_view_change                                (bool_show_outlines_               );
	app->set_dark_background_without_view_change                              (bool_dark_background_             );
	app->set_working_pulse_style                                              (bool_working_pulse_style_         );
	app->set_show_hydrogens_without_view_change                               (show_hydrogens_);
	app->set_side_chain_mode_without_view_change                              (sidechain_mode_, poseview::SideChainGeom::SHOW_IMMEDIATE_DURATION);

};


void
ViewPreset::save_settings_to_dict(util::DictionaryOP preset_dict, std::string tag_prefix){


	view_option_value2boolbatch_setter();
	str_show_hydrogens_ = poseview::SHOW_HYDROGEN_NAMES[show_hydrogens_];
	str_sidechain_mode_ = poseview::SideChainGeom::SHOW_MODE_NAMES[sidechain_mode_];

	preset_dict->set(tag_prefix + SHOW_CLASHES                      ,bool_show_clashes_               );
	preset_dict->set(tag_prefix + SHOW_EXPOSED                      ,bool_show_exposed_               );
	preset_dict->set(tag_prefix + SHOW_VOIDS                        ,bool_show_voids_                 );
	preset_dict->set(tag_prefix + SHOW_BACKBONE_ISSUES              ,bool_show_backbone_issues_       );
	preset_dict->set(tag_prefix + SHOW_BACKBONE_PINS                ,bool_show_backbone_pins_         );
	preset_dict->set(tag_prefix + SHOW_SHEET_HBONDS         	    ,bool_show_sheet_hbonds_          );
	preset_dict->set(tag_prefix + SHOW_HELIX_HBONDS         	    ,bool_show_helix_hbonds_          );
	preset_dict->set(tag_prefix + SHOW_LOOP_HBONDS                  ,bool_show_loop_hbonds_           );
	preset_dict->set(tag_prefix + SHOW_SIDECHAIN_HBONDS             ,bool_show_sidechain_hbonds_      );
	preset_dict->set(tag_prefix + SHOW_NON_PROTEIN_HBONDS           ,bool_show_non_protein_hbonds_    );
	preset_dict->set(tag_prefix + SHOW_BONDABLE_ATOMS               ,bool_show_bondable_atoms_        );
	preset_dict->set(tag_prefix + SHOW_CONSTRAINTS          	    ,bool_show_constraints_           );
	preset_dict->set(tag_prefix + SHOW_RESIDUE_BURIAL               ,bool_show_residue_burials_       );
	preset_dict->set(tag_prefix + SHOW_ISOSURFACE                   ,bool_show_isosurface_            );
	preset_dict->set(tag_prefix + SYM_CHAIN_VISIBLE         	    ,bool_sym_chain_visible_          );
	preset_dict->set(tag_prefix + SYM_CHAIN_COLORS          	    ,bool_sym_chain_colors_           );
	preset_dict->set(tag_prefix + SHOW_MUTATED_RESIDUES     	    ,bool_show_mutated_residues_      );
	preset_dict->set(tag_prefix + SHOW_SIDECHAINS_WITH_ISSUES       ,bool_show_sidechains_with_issues_);
	preset_dict->set(tag_prefix + SHOW_OUTLINES             	    ,bool_show_outlines_              );
	preset_dict->set(tag_prefix + DARK_BACKGROUND                   ,bool_dark_background_            );
	preset_dict->set(tag_prefix + WORKING_PULSE_STYLE       	    ,bool_working_pulse_style_        );
	preset_dict->set(tag_prefix + SHOW_HYDROGENS                    ,str_show_hydrogens_              );
	preset_dict->set(tag_prefix + SIDECHAIN_MODE                    ,str_sidechain_mode_              );

	util::save_presets_file();
};

void
ViewPreset::delete_settings_from_dict(util::DictionaryOP preset_dict, std::string tag_prefix){

	std::string preset_show_clashes                             = tag_prefix + SHOW_CLASHES;
	std::string preset_show_exposed                             = tag_prefix + SHOW_EXPOSED;
	std::string preset_show_voids                               = tag_prefix + SHOW_VOIDS;
	std::string preset_show_backbone_issues                     = tag_prefix + SHOW_BACKBONE_ISSUES;
	std::string preset_show_backbone_pins                       = tag_prefix + SHOW_BACKBONE_PINS;
	std::string preset_show_sheet_hbonds         	            = tag_prefix + SHOW_SHEET_HBONDS;
	std::string preset_show_helix_hbonds         	            = tag_prefix + SHOW_HELIX_HBONDS;
	std::string preset_show_loop_hbonds                         = tag_prefix + SHOW_LOOP_HBONDS;
	std::string preset_show_sidechain_hbonds                    = tag_prefix + SHOW_SIDECHAIN_HBONDS;
	std::string preset_show_non_protein_hbonds                  = tag_prefix + SHOW_NON_PROTEIN_HBONDS;
	std::string preset_show_bondable_atoms                      = tag_prefix + SHOW_BONDABLE_ATOMS;
	std::string preset_show_constraints          	            = tag_prefix + SHOW_CONSTRAINTS;
	std::string preset_show_residue_burial                      = tag_prefix + SHOW_RESIDUE_BURIAL;
	std::string preset_show_isosurface                          = tag_prefix + SHOW_ISOSURFACE;
	std::string preset_sym_chain_visible         	            = tag_prefix + SYM_CHAIN_VISIBLE;
	std::string preset_sym_chain_colors          	            = tag_prefix + SYM_CHAIN_COLORS;
	std::string preset_show_mutated_residues     	            = tag_prefix + SHOW_MUTATED_RESIDUES;
	std::string preset_show_sidechains_with_issues              = tag_prefix + SHOW_SIDECHAINS_WITH_ISSUES;
	std::string preset_show_outlines             	            = tag_prefix + SHOW_OUTLINES;
	std::string preset_dark_background                          = tag_prefix + DARK_BACKGROUND;
	std::string preset_working_pulse_style       	            = tag_prefix + WORKING_PULSE_STYLE;
	std::string preset_show_hydrogens                           = tag_prefix + SHOW_HYDROGENS;
	std::string preset_sidechain_mode                           = tag_prefix + SIDECHAIN_MODE;


	util::delete_preset_setting(preset_show_clashes                 	  );
	util::delete_preset_setting(preset_show_exposed                       );
	util::delete_preset_setting(preset_show_voids                         );
	util::delete_preset_setting(preset_show_backbone_issues               );
	util::delete_preset_setting(preset_show_backbone_pins                 );
	util::delete_preset_setting(preset_show_sheet_hbonds         	      );
	util::delete_preset_setting(preset_show_helix_hbonds         	      );
	util::delete_preset_setting(preset_show_loop_hbonds                   );
	util::delete_preset_setting(preset_show_sidechain_hbonds              );
	util::delete_preset_setting(preset_show_non_protein_hbonds            );
	util::delete_preset_setting(preset_show_bondable_atoms                );
	util::delete_preset_setting(preset_show_constraints          	      );
	util::delete_preset_setting(preset_show_residue_burial                );
	util::delete_preset_setting(preset_show_isosurface                    );
	util::delete_preset_setting(preset_sym_chain_visible         	      );
	util::delete_preset_setting(preset_sym_chain_colors          	      );
	util::delete_preset_setting(preset_show_mutated_residues     	      );
	util::delete_preset_setting(preset_show_hydrogens                     );
	util::delete_preset_setting(preset_sidechain_mode                     );
	util::delete_preset_setting(preset_show_sidechains_with_issues        );
	util::delete_preset_setting(preset_show_outlines             	      );
	util::delete_preset_setting(preset_dark_background                    );
	util::delete_preset_setting(preset_working_pulse_style       	      );
	util::save_presets_file();

};



void ViewPreset::bool2view_option_value_batch_setter(){

	bool2view_option_value(bool_show_clashes_               , show_clashes_               );
	bool2view_option_value(bool_show_exposed_               , show_exposed_               );
	bool2view_option_value(bool_show_voids_                 , show_voids_                 );
	bool2view_option_value(bool_show_backbone_issues_       , show_backbone_issues_       );
	bool2view_option_value(bool_show_backbone_pins_         , show_backbone_pins_         );
	bool2view_option_value(bool_show_sheet_hbonds_          , show_sheet_hbonds_          );
	bool2view_option_value(bool_show_helix_hbonds_          , show_helix_hbonds_          );
	bool2view_option_value(bool_show_loop_hbonds_           , show_loop_hbonds_           );
	bool2view_option_value(bool_show_sidechain_hbonds_      , show_sidechain_hbonds_      );
	bool2view_option_value(bool_show_non_protein_hbonds_    , show_non_protein_hbonds_    );
	bool2view_option_value(bool_show_bondable_atoms_        , show_bondable_atoms_        );
	bool2view_option_value(bool_show_constraints_           , show_constraints_           );
	bool2view_option_value(bool_show_residue_burials_       , show_residue_burial_        );
	bool2view_option_value(bool_show_isosurface_            , show_isosurface_            );
	bool2view_option_value(bool_sym_chain_visible_          , sym_chain_visible_          );
	bool2view_option_value(bool_sym_chain_colors_           , sym_chain_colors_           );
	bool2view_option_value(bool_show_mutated_residues_      , show_mutated_residues_      );
	bool2view_option_value(bool_show_sidechains_with_issues_, show_sidechains_with_issues_);
	bool2view_option_value(bool_show_outlines_              , show_outlines_              );
	bool2view_option_value(bool_dark_background_            , dark_background_            );
	bool2view_option_value(bool_working_pulse_style_        , working_pulse_style_        );

};


void
ViewPreset::view_option_value2boolbatch_setter(){
	view_option_value2bool(show_clashes_               ,bool_show_clashes_               );
	view_option_value2bool(show_exposed_               ,bool_show_exposed_               );
	view_option_value2bool(show_voids_                 ,bool_show_voids_                 );
	view_option_value2bool(show_backbone_issues_       ,bool_show_backbone_issues_       );
	view_option_value2bool(show_backbone_pins_         ,bool_show_backbone_pins_         );
	view_option_value2bool(show_sheet_hbonds_          ,bool_show_sheet_hbonds_          );
	view_option_value2bool(show_helix_hbonds_          ,bool_show_helix_hbonds_          );
	view_option_value2bool(show_loop_hbonds_           ,bool_show_loop_hbonds_           );
	view_option_value2bool(show_sidechain_hbonds_      ,bool_show_sidechain_hbonds_      );
	view_option_value2bool(show_non_protein_hbonds_    ,bool_show_non_protein_hbonds_    );
	view_option_value2bool(show_bondable_atoms_        ,bool_show_bondable_atoms_        );
	view_option_value2bool(show_constraints_           ,bool_show_constraints_           );
	view_option_value2bool(show_residue_burial_        ,bool_show_residue_burials_       );
	view_option_value2bool(show_isosurface_            ,bool_show_isosurface_            );
	view_option_value2bool(sym_chain_visible_          ,bool_sym_chain_visible_          );
	view_option_value2bool(sym_chain_colors_           ,bool_sym_chain_colors_           );
	view_option_value2bool(show_mutated_residues_      ,bool_show_mutated_residues_      );
	view_option_value2bool(show_sidechains_with_issues_,bool_show_sidechains_with_issues_);
	view_option_value2bool(show_outlines_              ,bool_show_outlines_              );
	view_option_value2bool(dark_background_            ,bool_dark_background_            );
	view_option_value2bool(working_pulse_style_        ,bool_working_pulse_style_        );
};


void ViewPreset::bool2view_option_value(const bool & in, ViewPreset::ViewOptionValue & out) {
	if (in == true) {
		out = ViewPreset::TRUE;
	} else if (in == false) {
		out = ViewPreset::FALSE;
	} else {
		out = ViewPreset::UNCHANGED;
	}
}

void ViewPreset::view_option_value2bool(const ViewPreset::ViewOptionValue &in, bool &out) {
	if (in == ViewPreset::TRUE) {
		out = true;
	} else if (in == ViewPreset::FALSE) {
		out = false;
	}
}


}// namespace gui
} // namespace interactive
