#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

//// variables
std::string filename = "default.sp";
int userNumberColumn = 4;
int userNumberRow = 4;
int userNumberlayer = 2; // has to be even number, divide by 2
std::string userCellName = "mr";
std::string userCellFlags = "s=1";
int userWordlineBitline = 1;
int userSelectLine = 1;
std::string userSheetResistance = "2.5";
std::string userLoadResistance = "100";
std::string userGroundNode = "vss";
std::string userVsense = "0.1";
std::string userVneutral = "0";
//// variables

// using namespace std;
void output(std::stringstream& tempMainStream, int& numberColumn, int& numberRow, int& numberlayer, \
	std::string& cellName, std::string& cellFlags, int& wordline_bitline, int& selectLine, \
	std::string& sheetResistance, std::string& loadResistance, std::string& groundNode, std::string& vsense, std::string& vneutral);
void print_usage(char * argv0);

int main (int argc, char *argv[])
{
	std::stringstream outputMainStream;

	for (int i=0; i<argc; i++)
	{
		if (i == 0)
		{
		}
		else if (argv[i]== std::string("-o"))
		{
			i++;
			filename = argv[i];
			std::cout << "Output File: " << filename << "\n";
		}
		else if (argv[i]== std::string("-cn"))
		{
			i++;
			userCellName = argv[i];
			std::cout << "Cell Name: " << userCellName << "\n";
		}
		else if (argv[i]== std::string("-cf"))
		{
			i++;
			userCellFlags = argv[i];
			std::cout << "Cell Flags: " << userCellFlags << "\n";
		}
		else if (argv[i]== std::string("-r"))
		{
			i++;
			userNumberRow = std::stoi(argv[i]);
			std::cout << "Number of Rows: " << userNumberRow << "\n";
		}
		else if (argv[i]== std::string("-c"))
		{
			i++;
			userNumberColumn = std::stoi(argv[i]);
			std::cout << "Number of Columns: " << userNumberColumn << "\n";
		}
		else if (argv[i]== std::string("-l"))
		{
			i++;
			userNumberlayer = std::stoi(argv[i]);
			std::cout << "Number of Layers: " << userNumberlayer << "\n";
		}
		else if (argv[i]== std::string("-wb"))
		{
			i++;
			userWordlineBitline = (std::stoi(argv[i]) != 2) ? 1 : 2;
			if (userWordlineBitline == 1)
			{
				std::cout << "Select Wordline"<< "\n";
			}
			else
			{
				std::cout << "Select Bitline"<< "\n";
			}
		}
		else if (argv[i]== std::string("-sl"))
		{
			i++;
			userSelectLine = std::stoi(argv[i]);
			std::cout << "Select Line: " << userSelectLine << "\n";
		}
		else if (argv[i]== std::string("-sr"))
		{
			i++;
			userSheetResistance = argv[i];
			std::cout << "Sheet Resistance: " << userSheetResistance << "\n";
		}
		else if (argv[i]== std::string("-lr"))
		{
			i++;
			userLoadResistance = argv[i];
			std::cout << "Load Resistance: " << userLoadResistance << "\n";
		}
		else if (argv[i]== std::string("-gn"))
		{
			i++;
			userGroundNode = argv[i];
			std::cout << "Ground Node: " << userGroundNode << "\n";
		}
		else if (argv[i]== std::string("-vs"))
		{
			i++;
			userVsense = argv[i];
			std::cout << "Sense Voltage: " << userVsense << "\n";
		}
		else if (argv[i]== std::string("-vn"))
		{
			i++;
			userVneutral = argv[i];
			std::cout << "Neutral Voltage: " << userVneutral << "\n";
		}
		else if (argv[i] == std::string("-h") || argv[i] == std::string("-help"))
		{
			print_usage(argv[0]);
		}
	}

    output(outputMainStream,userNumberColumn,userNumberRow,userNumberlayer,userCellName,userCellFlags,userWordlineBitline,userSelectLine, \
		userSheetResistance,userLoadResistance,userGroundNode,userVsense,userVneutral);
    
	std::ofstream tempOutputFile;
	tempOutputFile.open(filename.c_str());
	tempOutputFile << outputMainStream.str();
	tempOutputFile.close();

	exit(0);
}

void output(std::stringstream& tempMainStream, int& numberColumn, int& numberRow, int& numberlayer, \
	std::string& cellName, std::string& cellFlags, int& wordline_bitline, int& selectLine, \
	std::string& sheetResistance, std::string& loadResistance, std::string& groundNode, std::string& vsense, std::string& vneutral)
{
    
    const char *WB  = "wb";
    bool first = true;
    
    for( int cx = 1; cx <= numberlayer; ++cx )
	{
        for(int wb = 0; wb <= 1; ++wb)
		{
            if(!first)
			{
				tempMainStream << "/////////////////////////////////////////////////////\n\n";
			}

            for( int i = 1; i <= numberRow; ++i )
			{
                for( int j = 1; j <= numberColumn; ++j )
				{
                    if(cx == 1)
					{
						tempMainStream \
							<< "x" << WB[wb] << std::setfill('0') << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
							<< "c" << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
							<< WB[wb] << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
							<< cellName << "\t" << cellFlags << "\n";
                    }
                    else
					{
                        if(cx % 2 == wb % 2)
						{
							tempMainStream \
								<< "x" << WB[wb] << std::setfill('0') << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
								<< "c" << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
								<< WB[wb] << std::setw(2) << cx-1 << std::setw(4) << i << std::setw(4) << j << "\t" \
								<< cellName << "\t" << cellFlags << "\n";
                        }
                        else
						{
							tempMainStream \
								<< "x" << WB[wb] << std::setfill('0') << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
								<< "c" << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
								<< WB[wb] << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
								<< cellName << "\t" << cellFlags << "\n";
                        }
                    }
                }
            }
            first = false;
        }
    }
// w/b line R 
	for( int cx = 1; cx <= numberlayer; ++cx )
	{
		for(int wb = 0; wb <= 1; ++wb)
		{
			if(!first)
			{
				tempMainStream << "/////////////////////////////////////////////////////\n\n";
			}

		  	for(int i = 1; i <= numberRow; ++i)
			{
				for(int j = 1; j <= numberColumn; ++j)
				{
					int x = 0;
					int y = 0;
					if(cx == 1)
					{
						if (wb == 0)
						{
							if (j == 1)
							{
								tempMainStream \
									<< "r" << WB[wb] << std::setfill('0') << std::setw(2) << cx << std::setw(4) << i << "\t" \
									<< WB[wb] << std::setw(2) << cx << std::setw(4) << i << "\t" \
									<< WB[wb] << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
									<< sheetResistance << "\n";
							}
							else{
								tempMainStream \
									<< "r" << WB[wb] << std::setfill('0') << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
									<< WB[wb] << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j - 1 << "\t" \
									<< WB[wb] << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
									<< sheetResistance << "\n";
							}
						}

						if (wb == 1)
						{
							if (j == numberRow)
							{
								tempMainStream \
									<< "r" << WB[wb] << std::setfill('0') << std::setw(2) << cx << std::setw(4) << i << "\t" \
									<< WB[wb] << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
									<< WB[wb] << std::setw(2) << cx << std::setw(4) << i << "\t" \
									<< sheetResistance << "\n";
							}
							else
							{
								tempMainStream \
									<< "r" << WB[wb] << std::setfill('0') << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
									<< WB[wb] << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
									<< WB[wb] << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j + 1 << "\t" \
									<< sheetResistance << "\n";
							}
						}
					}
					else
					{
						if(cx % 2 == wb % 2)
						{
						} 
						else
						{
							if (wb == 0)
							{
								if (j == 1)
								{
									tempMainStream \
										<< "r" << WB[wb] << std::setfill('0') << std::setw(2) << cx << std::setw(4) << i << "\t" \
										<< WB[wb] << std::setw(2) << cx << std::setw(4) << i << "\t" \
										<< WB[wb] << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
										<< sheetResistance << "\n";
								}
								else
								{
									tempMainStream \
										<< "r" << WB[wb] << std::setfill('0') << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
										<< WB[wb] << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j - 1 << "\t" \
										<< WB[wb] << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
										<< sheetResistance << "\n";
								}
							}

							if ( wb == 1 )
							{
								if (j == numberRow)
								{
									tempMainStream \
										<< "r" << WB[wb] << std::setfill('0') << std::setw(2) << cx << std::setw(4) << i << "\t" \
										<< WB[wb] << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
										<< WB[wb] << std::setw(2) << cx << std::setw(4) << i << "\t" \
										<< sheetResistance << "\n";
								}
								else
								{
									tempMainStream \
										<< "r" << WB[wb] << std::setfill('0') << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
										<< WB[wb] << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
										<< WB[wb] << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j + 1 << "\t" \
										<< sheetResistance << "\n";
								}
							}
						}
					}
				}
			}
			first = false;
		}
	}
	
// cl line R
   for( int cx = 1; cx <= numberlayer; ++cx )
   {
	   	if(!first)
		{
			tempMainStream << "/////////////////////////////////////////////////////\n\n";
		}

		for( int i = 1; i <= numberRow; ++i )
		{
			for(int j = 1; j <= numberColumn; ++j)
			{
				if (i == numberRow)
				{
					tempMainStream \
						<< "rlc" << std::setfill('0') << std::setw(2) << cx << std::setw(4) << j << "\t" \
						<< "c" << std::setw(2) << cx << std::setw(4) << j << "\t" \
						<< "c" << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
						<< sheetResistance << "\n";
				}
				else
				{
					tempMainStream \
						<< "rlc" << std::setfill('0') << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
						<< "c" << std::setw(2) << cx << std::setw(4) << i << std::setw(4) << j << "\t" \
						<< "c" << std::setw(2) << cx << std::setw(4) << i + 1 << std::setw(4) << j << "\t" \
						<< sheetResistance << "\n";
				}
			}
		}
		first = false;
	}
//r

	for( int cx = 1; cx <= numberlayer; ++cx )
	{
		if(!first)
		{
			tempMainStream << "/////////////////////////////////////////////////////\n\n";
		}

		for(int j = 1; j <= numberRow; ++j)
		{
			tempMainStream \
				<< "rc" << std::setfill('0') << std::setw(2) << cx << std::setw(4) << j << "\t" \
				<< "c" << std::setw(2) << cx << std::setw(4) << j << "\t" \
				<< groundNode << "\t" \
				<< loadResistance << "\n";
		}    
		first = false;
	}


//vin
	for(int cx = 1; cx <= numberlayer; ++cx)
	{
		if(!first)
		{
			tempMainStream << "/////////////////////////////////////////////////////\n\n";
		}

		for(int j = 1; j <= numberColumn; ++j)
		{
			if ((j == selectLine) && (wordline_bitline == 1))
			{
				if(cx == 1)
				{
					tempMainStream \
						<< "vw" << std::setfill('0') << std::setw(2) << cx << std::setw(4) << j << "\t" \
						<< "w" << std::setw(2) << cx << std::setw(4) << j << "\t" \
						<< groundNode << "\t" \
						<< vsense << "\n";
				}
				else
				{
					if(cx % 2 == 0)
					{
					} 
					else
					{
						tempMainStream \
						<< "vw" << std::setfill('0') << std::setw(2) << cx << std::setw(4) << j << "\t" \
						<< "w" << std::setw(2) << cx << std::setw(4) << j << "\t" \
						<< groundNode << "\t" \
						<< vsense << "\n";
					}
				}
			}
			else
			{
				if(cx == 1)
				{
					tempMainStream \
						<< "vw" << std::setfill('0') << std::setw(2) << cx << std::setw(4) << j << "\t" \
						<< "w" << std::setw(2) << cx << std::setw(4) << j << "\t" \
						<< groundNode << "\t" \
						<< vneutral << "\n";
				}
				else
				{
					if(cx % 2 == 0)
					{
					} 
					else
					{
						tempMainStream \
						<< "vw" << std::setfill('0') << std::setw(2) << cx << std::setw(4) << j << "\t" \
						<< "w" << std::setw(2) << cx << std::setw(4) << j << "\t" \
						<< groundNode << "\t" \
						<< vneutral << "\n";
					}
				}
			}
		
		}
		
		for( int i = 1; i <= numberRow; ++i )
		{
			if (i == selectLine && wordline_bitline == 2)
			{
				if(cx == 1)
				{
					tempMainStream \
						<< "vb" << std::setfill('0') << std::setw(2) << cx << std::setw(4) << i << "\t" \
						<< "b" << std::setw(2) << cx << std::setw(4) << i << "\t" \
						<< groundNode << "\t" \
						<< vsense << "\n";
				}
				else
				{
					if(cx % 2 == 1)
					{
					} 
					else
					{
						tempMainStream \
						<< "vb" << std::setfill('0') << std::setw(2) << cx << std::setw(4) << i << "\t" \
						<< "b" << std::setw(2) << cx << std::setw(4) << i << "\t" \
						<< groundNode << "\t" \
						<< vsense << "\n";
					}
				}
			}
			else
			{
				if(cx == 1)
				{
					tempMainStream \
						<< "vb" << std::setfill('0') << std::setw(2) << cx << std::setw(4) << i << "\t" \
						<< "b" << std::setw(2) << cx << std::setw(4) << i << "\t" \
						<< groundNode << "\t" \
						<< vneutral << "\n";
				}
				else
				{
					if(cx % 2 == 1)
					{
					} 
					else
					{
						tempMainStream \
						<< "vb" << std::setfill('0') << std::setw(2) << cx << std::setw(4) << i << "\t" \
						<< "b" << std::setw(2) << cx << std::setw(4) << i << "\t" \
						<< groundNode << "\t" \
						<< vneutral << "\n";
					}
				}
			}
		}
		first = false;
	}
}


void print_usage(char * argv0)
{
	std::cerr << "------------------------------------" << "\n";
	std::cerr << "How to use 3-D HIM SPICE netlist generator:" <<"\n";
	std::cerr << "./him_gen" << "\n";
	std::cerr << "===================================" << "\n";
	std::cerr << " -o  <default.sp>" << "\n";
	std::cerr << "		string, define output file name" << "\n";
	std::cerr << " -cn  <mr>" << "\n";
	std::cerr << "		string, define cell name" << "\n";
	std::cerr << " -cf  <s=0>" << "\n";
	std::cerr << "		string, define cell flags" << "\n";
	std::cerr << " -r  <4>" << "\n";
	std::cerr << "		int, define number of rows" << "\n";
	std::cerr << " -c  <4>" << "\n";
	std::cerr << "		int, define number of columns" << "\n";
	std::cerr << " -l  <2>" << "\n";
	std::cerr << "		int, define number of layers, define n*2 layers of crossbar array" << "\n";
	std::cerr << " -wb  <1>" << "\n";
	std::cerr << "		int, 1/2, define wordline (1) or bitline (2) group" << "\n";
	std::cerr << " -sl  <1>" << "\n";
	std::cerr << "		int, less than or equal to number of rows, define the line of the sensing drive" << "\n";
	std::cerr << " -sr  <2.5>" << "\n";
	std::cerr << "		string, define sheet resistance" << "\n";
	std::cerr << " -lr  <100>" << "\n";
	std::cerr << "		string, define load resistance" << "\n";
	std::cerr << " -gn  <vss>" << "\n";
	std::cerr << "		string, define ground node" << "\n";
	std::cerr << " -vs  <0.1>" << "\n";
	std::cerr << "		string, define drive voltage" << "\n";
	std::cerr << " -vn  <0>" << "\n";
	std::cerr << "		string, define neutral voltage" << "\n";
	std::cerr << "optional:" << "\n";
	std::cerr << " -h -help" << "\n";
	std::cerr << " 		help" << "\n";
	std::cerr << "=============================================================================" << "\n";
	std::cerr << "3-D HIM SPICE netlist generator is developed in the Department of Electrical and Computer Engineering, University of Pittsburgh" << "\n";
    std::cerr << "V2.0 is developed in the Department of Electrical and Computer Engineering, Tennessee State University" << "\n";
	std::cerr << "Yi-Chung Chen" << "\n";
	exit(1);
}
