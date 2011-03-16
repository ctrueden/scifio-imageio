/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

/*
OME Bio-Formats ITK plugin for calling Bio-Formats from the Insight Toolkit.
Copyright (c) 2008, UW-Madison LOCI.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the UW-Madison LOCI nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY UW-MADISON LOCI ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL UW-MADISON LOCI BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
IMPORTANT NOTE: Although this specific file is distributed according to a
"BSD-style" license and the Apache 2 license, it requires to be linked to the
OME Bio-Formats Java library at run-time to do anything useful. The OME
Bio-Formats Java library is licensed under the GPL v2 or later.  Therefore, if
you wish to distribute this software in binary form with Bio-Formats itself,
your combined binary work must be distributed under the terms of the GPL v2
or later license.
*/

/*
Adapted from the Slicer3 project: http://www.slicer.org/
http://viewvc.slicer.org/viewcvs.cgi/trunk/Libs/MGHImageIO/

See slicer-license.txt for Slicer3's licensing information.
*/

#ifndef __itkBioFormatsImageIO_h
#define __itkBioFormatsImageIO_h

// ITK includes
#include "itkImageIOBase.h"
#include <sstream>
#include <iostream>

namespace itk
{

/** \class BioFormatsImageIO
 *
 * \brief Interface to the Bio-Formats Java Library.
 *
 * This class provides an adaptor gate to use all the file formats supported by
 * the Bio-Formats Java library.
 *
 * \warning Note that the Bio-Format Java library is distributed under a GPLv2
 * license. For details, see http://www.loci.wisc.edu/software/bio-formats
 */
class BioFormatsImageIO : public ImageIOBase
{
public:
  typedef BioFormatsImageIO           Self;
  typedef ImageIOBase                 Superclass;
  typedef SmartPointer<Self>          Pointer;
  typedef SmartPointer<const Self>    ConstPointer;

  /** Method for creation through the object factory **/
  itkNewMacro(Self);
  /** RTTI (and related methods) **/
  itkTypeMacro(BioFormatsImageIO, Superclass);

  /**--------------- Read the data----------------- **/
  virtual bool CanReadFile(const char* FileNameToRead);
  /* Set the spacing and dimension information for the set file name */
  virtual void ReadImageInformation();
  /* Read the data from the disk into provided memory buffer */
  virtual void Read(void* buffer);

  /**---------------Write the data------------------**/
  virtual bool CanWriteFile(const char* FileNameToWrite);
  /* Set the spacing and dimension information for the set file name */
  virtual void WriteImageInformation();
  /* Write the data to the disk from the provided memory buffer */
  virtual void Write(const void* buffer);

protected:
  BioFormatsImageIO();
  ~BioFormatsImageIO();

private:
  std::string m_JavaCommand;
  std::string m_ClassPath;

  template <typename ReturnType>
  ReturnType valueOf( const std::string &s )
  {
    ReturnType res;
    std::istringstream(s) >> res;
    return res;
  }

  char ** toCArray( std::vector< std::string > & args )
  {
    char **argv = new char *[args.size() + 1];
    for( int i = 0; i < static_cast< int >( args.size() ); i++ )
      {
      itkDebugMacro( "BioFormatsImageIO::toCArray::args["<<i<<"] = " << args[i]);
      argv[i] = (char*)args[i].c_str();
      }
    argv[args.size()] = NULL;
    return argv;
  }

};

}

#endif
