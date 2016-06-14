/* This file is part of Lemma, a geophysical modelling and inversion API */

/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
  @file
  @author   Trevor Irons
  @date     01/28/2010
  @version  $Id: hankeltransform.h 270 2015-08-24 15:45:41Z tirons $
 **/

#ifndef __hankeltransform_h
#define __hankeltransform_h

#include "LemmaObject.h"
#include "kernelem1dbase.h"
#include "kernelem1dspec.h"
#include "kernelem1dmanager.h"

namespace Lemma {

        // ===================================================================
        //        Class:  HankelTransform
        /// \brief  Pure abstract class for hankel transforms
        /// \details
        // ===================================================================
        class HankelTransform : public LemmaObject {

            public:

                /// Prints out basic info about the class
                friend std::ostream &operator<<(std::ostream &stream,
                        const HankelTransform &ob);

                // ====================  LIFECYCLE     =======================

                //static HankelTransform* New();

                //void Delete();

                // ====================  OPERATORS     =======================

                // ====================  OPERATIONS    =======================

                /// @todo this is actually a deprecated function. Only Chave
                ///   uses this.
                /// Performs numerical integration using Gaussian quadrature
                /// ikk:   type of kernel depending on source and receiver couple
                /// imode: a switch for TE(0) and TM(1) mode
                /// itype: order of Bessel function
                /// rho is argument to integral
                /// wavef is the propogation constant of free space
                /// = omega * sqrt( EP*AMU )  amu = 4 pi e-7  ep = 8.85e-12
                virtual Complex Zgauss(const int &ikk, const EMMODE &imode,
                            const int &itype, const Real &rho,
                            const Real &wavef, KernelEm1DBase *Kernel)=0;

                /// Computes related kernels, if applicable, otherwise this is
                /// just a dummy function.
                virtual void ComputeRelated(const Real& rho, KernelEm1DBase* Kernel);

                virtual void ComputeRelated(const Real& rho, std::vector< KernelEm1DBase* > KernelVec);

                virtual void ComputeRelated(const Real& rho, KernelEM1DManager* KernelManager);

                // ====================  ACCESS        =======================

                // ====================  INQUIRY       =======================

                // ====================  DATA MEMBERS  =======================

            protected:

                // ====================  LIFECYCLE     =======================

                /// Default protected constructor.
                HankelTransform (const std::string &name);

                /// Default protected constructor.
                ~HankelTransform ();

            private:

    }; // -----  end of class  HankelTransform  -----

}

#endif // __hankeltransform_h