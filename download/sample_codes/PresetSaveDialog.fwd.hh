// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington UW TechTransfer, email: license@u.washington.edu.

#ifndef INCLUDED__STANDALONE_APPLICATION_PRESET_SAVE_DIALOG_FWD_HH
#define INCLUDED__STANDALONE_APPLICATION_PRESET_SAVE_DIALOG_FWD_HH

#include <interactive/util/refcount/access_ptr.hh>
#include <interactive/util/refcount/owning_ptr.hh>
#include <utility/vector1.hh>

namespace standalone {
namespace application {

class PresetSaveDialog;
typedef interactive::util::access_ptr< PresetSaveDialog > PresetSaveDialogAP;
typedef interactive::util::access_ptr< PresetSaveDialog const > PresetSaveDialogCAP;
typedef interactive::util::owning_ptr< PresetSaveDialog > PresetSaveDialogOP;
typedef interactive::util::owning_ptr< PresetSaveDialog const > PresetSaveDialogCOP;
typedef utility::vector1< PresetSaveDialogOP > PresetSaveDialogOPs;
typedef utility::vector1< PresetSaveDialogCAP >  PresetSaveDialogCAPs;


} // namespace application
} // namespace standalone

#endif // INCLUDED__STANDALONE_APPLICATION_PRESET_SAVE_DIALOG_FWD_HH
