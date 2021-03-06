/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2021 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::fv::function2HeatTransfer

Description
    Function2 heat transfer model. The 2D function returns the heat transfer
    coefficient as a function of the local and neighbouring velocity
    magnitudes. An area-per-unit-volume [1/m] field (AoV) must be provided in
    constant.

\*---------------------------------------------------------------------------*/

#ifndef function2HeatTransfer_H
#define function2HeatTransfer_H

#include "interRegionHeatTransferModel.H"
#include "Function2.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace fv
{

/*---------------------------------------------------------------------------*\
                    Class function2HeatTransfer Declaration
\*---------------------------------------------------------------------------*/

class function2HeatTransfer
:
    public interRegionHeatTransferModel
{
    // Private Data

        //- Name of velocity field; default = U
        word UName_;

        //- Name of neighbour velocity field; default = U
        word UNbrName_;

        //- Heat transfer coefficient function ptr
        mutable autoPtr<Function2<scalar>> htcFunc_;

        //- Area per unit volume of heat exchanger
        mutable autoPtr<volScalarField> AoV_;

        //- Start time name
        const word startTimeName_;


    // Private Member Functions

        //- Non-virtual read
        void readCoeffs();

        //- Calculate the heat transfer coefficient
        virtual void correctHtc() const;


public:

    //- Runtime type information
    TypeName("function2HeatTransfer");


    // Constructors

        //- Construct from dictionary
        function2HeatTransfer
        (
            const word& name,
            const word& modelType,
            const dictionary& dict,
            const fvMesh& mesh
        );


    //- Destructor
    virtual ~function2HeatTransfer();


    // Member Functions

        //- Read dictionary
        virtual bool read(const dictionary& dict);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace fv
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
