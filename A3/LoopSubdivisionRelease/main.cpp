//////////////////////////////////////////////////////////////////////
//
//  University of Leeds
//  COMP 5812M Foundations of Modelling & Rendering
//  User Interface for Coursework
//
//  September, 2020
//
//  -----------------------------
//  main.cpp
//  -----------------------------
//  
//  Loads assets, then passes them to the render window. This is very far
//  from the only way of doing it.
//  
////////////////////////////////////////////////////////////////////////

// system libraries
#include <iostream>
#include <fstream>

// QT
#include <QApplication>

// local includes
#include "RenderWindow.h"
#include "DirectedEdgeSurface.h"
#include "RenderParameters.h"
#include "RenderController.h"
#include "SubDivisionTools.h"
#include <string>
// main routine
int main(int argc, char **argv)
    { // main()
    // initialize QT
    QApplication renderApp(argc, argv);

    // check the args to make sure there's an input file
    if (argc != 2) 
        { // bad arg count
        // print an error message
        std::cout << "Usage: " << argv[0] << " geometry" << std::endl; 
        // and leave
        return 0;
        } // bad arg count

    //  use the argument to create a height field &c.
    DirectedEdgeSurface DirectedEdgeSurface;

    // open the input files for the geometry & texture
    std::ifstream geometryFile(argv[1]);

    // try reading it
    if (!(geometryFile.good()) || (!DirectedEdgeSurface.ReadObjectStream(geometryFile)))
        { // object read failed 
        std::cout << "Read failed for object " << argv[1] << " or texture " << argv[2] << std::endl;
        return 0;
        } // object read failed


    for(int i=0;i<3;i++){
        updateHalfEdges(&DirectedEdgeSurface);
        updateExistedVertex(&DirectedEdgeSurface);
        subVertexs(&DirectedEdgeSurface);
        updateNormal(&DirectedEdgeSurface);
        for(int i=0;i<DirectedEdgeSurface.existedVertexBuffer.size();i++){
            DirectedEdgeSurface.vertices[i] = DirectedEdgeSurface.existedVertexBuffer[i];
        }

    }

    // dump the file to out
     std::string inputFileName = std::string(argv[1]);
     std::string outputFileName = inputFileName.substr(0,inputFileName.find_last_of('.'));
//     outputFileName = outputFileName.substr(outputFileName.find_last_of('\\'));
//     cout<<outputFileName<<endl;
     std::string outputPath = outputFileName+"_new.diredgenormal";
     std::cout<<outputPath<<std::endl;

     std::ofstream outpufFile(outputPath);
     DirectedEdgeSurface.WriteObjectStream(outpufFile);
     outpufFile.close();
    // create some default render parameters
    RenderParameters renderParameters;

    // use the object & parameters to create a window
    RenderWindow renderWindow(&DirectedEdgeSurface, &renderParameters, argv[1]);

    // create a controller for the window
    RenderController renderController(&DirectedEdgeSurface, &renderParameters, &renderWindow);

    //  set the initial size
    renderWindow.resize(762, 664);

    // show the window
    renderWindow.show();

    // set QT running
    return renderApp.exec();
    } // main()
