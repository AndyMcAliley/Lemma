/* This file is part of Lemma, a geophysical modelling and inversion API */

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
  @file
  @author   Trevor Irons
  @date     06/25/2009
  @version  $Id: LemmaObject.cpp 266 2015-04-01 03:24:00Z tirons $
 **/

#include "LemmaObject.h"

namespace Lemma {

    //LemmaObject::CName = std::string("LemmaObject");

    YAML::Emitter& operator << (YAML::Emitter& out, const LemmaObject& ob) {
        out << YAML::BeginMap;
        out << YAML::Key <<"Class Name"    << YAML::Value << ob.GetName();
        return out;
    }

    // ====================  LIFECYCLE     ==============================

    // Constructor
    LemmaObject::LemmaObject(const std::string& name) : Name(name) {
    }

    LemmaObject::LemmaObject(const YAML::Node &node) : Name(node.Tag()) {
    }

    // Destructor
    LemmaObject::~LemmaObject() {
    }

    // ====================  OPERATIONS    ==============================

    // ====================  INQUIRY       ==============================

    std::string LemmaObject::GetName() const {
        return Name;
    }

    // ====================  ACCESS        ==============================

    // ====================  ACCESS        ==============================

    // ====================  OPERATORS     ==============================

    //////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////

    DeSerializeTypeMismatch::DeSerializeTypeMismatch(const std::string& expected, const std::string& got) :
        runtime_error("DESERIALIZE TYPE MISMATCH") {
            std::cerr << "Expected " << expected << " got " << got << std::endl;
        }

    RequestToReturnNullPointer::
        RequestToReturnNullPointer(LemmaObject *ptr) :
        runtime_error("REQUEST TO RETURN NULL POINTER"){
            std::cerr << "Thrown by instance of "
                      << ptr->GetName() << std::endl;
        }

    MatFileCannotBeOpened::
        MatFileCannotBeOpened() :
        runtime_error("MATFILE CANNOT BE OPENED"){}

    AssignmentOutOfBounds::
        AssignmentOutOfBounds(LemmaObject *ptr) :
        runtime_error("ASSIGNMENT OUT OF BOUNDS"){
            std::cerr << "Thrown by instance of "
                      << ptr->GetName() << std::endl;
       }

	GenericFileIOError::
		GenericFileIOError(LemmaObject *ptr, const std::string &filename) : runtime_error("FILE I/O ERROR"){
			std::cerr << std::endl;
			std::cerr << "FILE I/O ERROR" << std::endl;
			std::cerr << std::endl;
			std::cerr << "Thrown by instance of "
				<< ptr->GetName() << std::endl;
			std::cerr << "  while trying to access " << filename << std::endl;
			std::cerr << std::endl;
		}

} // end of namespace Lemma
