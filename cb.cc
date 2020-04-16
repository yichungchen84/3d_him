// 3-D HIM Crossbar netlist generator for SPICE: Yi-Chung Chen, University of Pittsburgh, Sep. 30th, 2013
// Simplified from 3D-HIM generator
// Adding C model.
// any problem, please contact: YiChung.Chen.84@gmail.com 

/////////////////////////
//
// mr is memristor/RRAM component name.
// S is initial state of memristor/RRAM. need correspondng setup in verilogA
// S should be decimal.
//
/////////////////////////


#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

//// variables
std::string filename = "default.sp";
int userNumberColumn = 4;
int userNumberRow = 4;
std::string userCellName = "mr";
std::string userCellFlags = "s=0";
int userSelectLine = 1;
std::string userSheetResistance = "2.5";
std::string userParasiticCapacitance = "0.1f";
std::string userLoadResistance = "100";
std::string userBulkNode = "vss";
std::string userGroundNode = "vss";
std::string userVsense = "0.1";
std::string userVneutral = "0";
//// variables


void output(std::stringstream& tempMainStream, int& numberColumn, int& numberRow, \
	std::string& cellName, std::string& cellFlags, int& selectLine, \
	std::string& sheetResistance, std::string& parasiticCapacitance, std::string& loadResistance, \
    std::string& bulkNode, std::string& groundNode, std::string& vsense, std::string& vneutral);
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
        else if (argv[i]== std::string("-pc"))
		{
			i++;
			userSheetResistance = argv[i];
			std::cout << "Parasitic Capacitance: " << userParasiticCapacitance << "\n";
		}
		else if (argv[i]== std::string("-lr"))
		{
			i++;
			userLoadResistance = argv[i];
			std::cout << "Load Resistance: " << userLoadResistance << "\n";
		}
		else if (argv[i]== std::string("-bn"))
		{
			i++;
			userBulkNode = argv[i];
			std::cout << "Bulk Node: " << userBulkNode << "\n";
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
    
    output(outputMainStream,userNumberColumn,userNumberRow,userCellName,userCellFlags,userSelectLine, \
		userSheetResistance,userParasiticCapacitance,userLoadResistance,userBulkNode,userGroundNode,userVsense,userVneutral);
    
	std::ofstream tempOutputFile;
	tempOutputFile.open(filename.c_str());
	tempOutputFile << outputMainStream.str();
	tempOutputFile.close();

	exit(0);
}

void output(std::stringstream& tempMainStream, int& numberColumn, int& numberRow, \
	std::string& cellName, std::string& cellFlags, int& selectLine, \
	std::string& sheetResistance, std::string& parasiticCapacitance, std::string& loadResistance, \
    std::string& bulkNode, std::string& groundNode, std::string& vsense, std::string& vneutral)
{

    for( int i = 1; i <= numberRow; ++i )
    {
        for( int j = 1; j <= numberColumn; ++j )
        {
            tempMainStream \
                << "xw" << std::setfill('0') << std::setw(4) << i << std::setw(4) << j << "\t" \
                << "w" << std::setw(4) << i << std::setw(4) << j << "\t" \
                << "b" << std::setw(4) << i << std::setw(4) << j << "\t" \
                << cellName << "\t" << cellFlags << "\n";


        }
    }

    tempMainStream << "/////////////////////////////////////////////////////\n\n";

    for(int i = 1; i <= numberRow; ++i)
    {
        for(int j = 1; j <= numberColumn; ++j)
        {
            int x = 0;

            if (j == 1)
            {
                tempMainStream \
                    << "rw" << std::setfill('0') << std::setw(4) << i << "\t" \
                    << "w" << std::setw(4) << i << "\t" \
                    << "w" << std::setw(4) << i << std::setw(4) << j << "\t" \
                    << sheetResistance << "\n";

                // // Parsitic Capacitance
                // tempMainStream \
                //     << "cw" << std::setfill('0') << std::setw(4) << i << std::setw(4) << j << "\t" \
                //     << "w" << std::setw(4) << i << std::setw(4) << j << "\t" \
                //     << bulkNode<< "\t" \
                //     << parasiticCapacitance << "\n";
                // // Parsitic Capacitance
            }
            else
            {
                tempMainStream \
                    << "rw" << std::setfill('0') << std::setw(4) << i << std::setw(4) << j << "\t" \
                    << "w" << std::setw(4) << i << std::setw(4) << j - 1 << "\t" \
                    << "w" << std::setw(4) << i << std::setw(4) << j << "\t" \
                    << sheetResistance << "\n";

                // // Parsitic Capacitance
                // tempMainStream \
                //     << "cw" << std::setfill('0') << std::setw(4) << i << std::setw(4) << j << "\t" \
                //     << "w" << std::setw(4) << i << std::setw(4) << j << "\t" \
                //     << bulkNode<< "\t" \
                //     << parasiticCapacitance << "\n";
                // // Parsitic Capacitance
            }
        }
    }

    tempMainStream << "/////////////////////////////////////////////////////\n\n";
	
// bitline R C
    for(int i = 1; i <= numberRow; ++i)
    {
        for(int j = 1; j <= numberColumn; ++j)
        {
            if (i == numberRow)
            {
                tempMainStream \
                    << "rb" << std::setfill('0') << std::setw(4) << j << "\t" \
                    << "b" << std::setw(4) << j << "\t" \
                    << "b" << std::setw(4) << i << std::setw(4) << j << "\t" \
                    << sheetResistance << "\n";

                // // Parsitic Capacitance
                // tempMainStream \
                //     << "cb" << std::setfill('0') << std::setw(4) << i << std::setw(4) << j << "\t" \
                //     << "b" << std::setw(4) << i << std::setw(4) << j << "\t" \
                //     << bulkNode<< "\t" \
                //     << parasiticCapacitance << "\n";
                // // Parsitic Capacitance
            }
            else
            {
                tempMainStream \
                    << "rb" << std::setfill('0') << std::setw(4) << i << std::setw(4) << j << "\t" \
                    << "b" << std::setw(4) << i << std::setw(4) << j << "\t" \
                    << "b" << std::setw(4) << i + 1 << std::setw(4) << j << "\t" \
                    << sheetResistance << "\n";


                // // Parsitic Capacitance
                // tempMainStream \
                //     << "cb" << std::setfill('0') << std::setw(4) << i << std::setw(4) << j << "\t" \
                //     << "b" << std::setw(4) << i << std::setw(4) << j << "\t" \
                //     << bulkNode<< "\t" \
                //     << parasiticCapacitance << "\n";
                // // Parsitic Capacitance
            }
        }
    }


    tempMainStream << "/////////////////////////////////////////////////////\n\n";

    for(int j = 1; j <= numberColumn; ++j)
    {
        tempMainStream \
            << "rb" << std::setfill('0') << std::setw(4) << j << "\t" \
            << "b" << std::setw(4) << j << "\t" \
            << groundNode << "\t" \
            << loadResistance << "\n";
    }    

    tempMainStream << "/////////////////////////////////////////////////////\n\n";

    for(int j = 1; j <= numberColumn; ++j)
    {
        if (j == selectLine)
        {
            tempMainStream \
                    << "vw" << std::setfill('0') << std::setw(4) << j << "\t" \
                    << "w" << std::setw(4) << j << "\t" \
                    << groundNode << "\t" \
                    << vsense << "\n";
        }
        else
        {
            tempMainStream \
                << "vw" << std::setfill('0') << std::setw(4) << j << "\t" \
                << "w" << std::setw(4) << j << "\t" \
                << groundNode << "\t" \
                << vneutral << "\n";
        }
    
    }

    tempMainStream << "/////////////////////////////////////////////////////\n\n";
}


void print_usage(char * argv0)
{
	std::cerr << "------------------------------------" << "\n";
	std::cerr << "How to use Crossbar SPICE netlist generator:" <<"\n";
	std::cerr << "./cb" << "\n";
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
	std::cerr << " -sl  <1>" << "\n";
	std::cerr << "		int, less than or equal to number of rows, define the line of the sensing drive" << "\n";
	std::cerr << " -sr  <2.5>" << "\n";
	std::cerr << "		string, define sheet resistance" << "\n";
    std::cerr << " -pc  <0.1f>" << "\n";
	std::cerr << "		string, define parasitic capacitance" << "\n";
	std::cerr << " -lr  <100>" << "\n";
	std::cerr << "		string, define load resistance" << "\n";
	std::cerr << " -bn  <vss>" << "\n";
	std::cerr << "		string, define bulk node" << "\n";
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
	std::cerr << "Crossbar SPICE netlist generator is developed in the Department of Electrical and Computer Engineering, University of Pittsburgh" << "\n";
    std::cerr << "V2.0 is developed in the Department of Electrical and Computer Engineering, Tennessee State University" << "\n";
	std::cerr << "Yi-Chung Chen" << "\n";
	exit(1);
}
