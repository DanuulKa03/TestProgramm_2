#include "ListFrame.h"

void ListFrame::LoadFromfile(const std::string fileName)
{
    std::ifstream file(fileName, std::ios::binary);

    // Проверка на успешное открытие файла
    if (!file.is_open())
    {
        std::cerr << "Не удалось открыть файл: " << fileName << std::endl;
        return void();
    }

    size_t n = 0;
    while ( !file.eof() )
    {
        frameList.emplace_back();   
        file.seekg(2, std::ios_base::cur);
        file.read( frameList[n].identifier, Frame::sizeIdentifier );
        file.seekg( Frame::sizeOffInformation, std::ios_base::cur );
        file.read( frameList[n].address, Frame::sizeAddress );
        file.read( frameList[n].command, Frame::sizeCommand );
        file.read( frameList[n].dataLength, Frame::sizeDataLength );

        service(frameList[n], file, n);

        if (frameList[n].getDataLengthtoInt() > 0)
        {
            frameList[n].arrayData = new char[ frameList[n].getDataLengthtoInt() ];
            file.read( frameList[n].arrayData, frameList[n].getDataLengthtoInt() );
        }
        else if (frameList[n].getDataLengthtoInt() < 0)
        {
            frameList.pop_back();
            break;
        }
        file.seekg( 4, std::ios_base::cur );

        n++;
    }
    file.close();

}

void ListFrame::SaveToText(const std::string txtFileName)
{
    std::ofstream file(txtFileName);

    if (!file.is_open())
    {
        std::cerr << "Не удалось открыть файл: " << txtFileName << std::endl;
        return void();
    }
    
    file << std::left << std::setw(12) << "index" << std::setw(12) << "id" << std::setw(12) << "address" << std::setw(12)
        << "command" << std::setw(12) << "dataLength" << std::endl;

    for (size_t i = 0; i < frameList.size(); i++)
    {
        insertDataToFile(frameList[i], file, i);
    }
    
    file.close();
    std::cout << "File create." << std::endl;
}

//Функия нужна, чтобы просто сделать char в формате HEX
int ListFrame::charToInt(const char symbol)
{
    return static_cast<int>(static_cast<unsigned char>( symbol ));
}

void ListFrame::insertDataToFile(Frame& frame, std::ofstream& file, size_t n)
{
        file << std::setw(12) << n;

        //здесь используется setw() так как я осуществляю вставку по байтово. Чтобы первый байт сделал отступa
        for (size_t i = 0; i < Frame::sizeIdentifier - 1; i++)
        {
            file << frame.identifier[i];
        }
        file << std::setw(12 - Frame::sizeIdentifier + 1) << frame.identifier[Frame::sizeIdentifier - 1];


        for (size_t i = 0; i < Frame::sizeAddress - 1; i++)
        {
            file << std::hex << charToInt(frame.address[i]);
        }
        file << std::setw(12 - Frame::sizeAddress + 1) << frame.address[Frame::sizeAddress - 1];

        for (size_t i = 0; i < Frame::sizeCommand - 1; i++)
        {
            file << std::hex << charToInt(frame.command[i]);
        }
        file << std::hex << std::setw(12 - Frame::sizeCommand + 1) << frame.command[Frame::sizeCommand - 1];


        file << std::dec << std::setw(12) << frame.getDataLengthtoInt();

        file << std::endl;

}

void ListFrame::service(Frame& frame, std::ifstream& file, size_t n)
{
    std::cout << "DataLength [" << n << "]" << std::endl;

    for (size_t i = 0; i < Frame::sizeDataLength; i++)
    {
        std::cout << std::hex << charToInt(frame.dataLength[i]) << " ";
    }

    std::cout << std::endl << "Address" << std::endl;

    std::streampos currentPosition = file.tellg();

    std::cout << std::hex << std::setw(8) << std::setfill('0') << currentPosition << std::endl;

    std::cout << std::dec << "Size: " << frame.getDataLengthtoInt() << std::endl << "Teelg: " << file.tellg() << std::endl;

}
