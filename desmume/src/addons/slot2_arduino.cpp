/*
Copyright (C) 2021-2022 Arey Ferrero Ramos

This file is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This file is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with the this software.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <windows.h>

#include "../slot2.h"

class Slot2_Arduino : public ISlot2Interface
{
private:
	HANDLE handleCom3;
	bool fileSuccess;
	TCHAR *pcCom3Port;

public:
	virtual Slot2Info const* info()
	{
		static Slot2InfoSimple info("Arduino", "Arduino device emulator", 0x09);
		printf("\nProva mostrar informació.");
		return &info;
	}

	virtual void connect()
	{
		printf("\nProva inici connexió");
		handleCom3 = CreateFileA(pcCom3Port, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

		if (handleCom3 == INVALID_HANDLE_VALUE)
		{
			printf("The Com3 Port cannot be opened. The function CreateFileA() has failed with error %d.\n", GetLastError());
		}
		printf("\nProva final connexió.");
		// Aquí s'haurà de fer la escritura de fitxer: WriteFile().
	}

	virtual void disconnect()
	{
		fileSuccess = CloseHandle(handleCom3);

		if (!fileSuccess)
		{
			printf("The Com3 Port cannot be closed. The function CloseHandle() has failed with error %d.\n", GetLastError());
		}
	}

	virtual void shutdown()
	{
		fileSuccess = DeleteFileA(pcCom3Port);

		if (!fileSuccess)
		{
			printf("The Com3 Port cannot be deleted. The function DeleteFileA() has failed with error %d.\n", GetLastError());
		}
	}

	virtual void writeByte(u8 PROCNUM, u32 addr, u8 val)
	{

	}

	virtual void writeWord(u8 PROCNUM, u32 addr, u16 val)
	{

	}

	virtual void writeLong(u8 PROCNUM, u32 addr, u32 val)
	{

	}

	virtual u8 readByte(u8 PROCNUM, u32 addr)
	{
		return 0x00;
	}

	virtual u16 readWord(u8 PROCNUM, u32 addr)
	{
		return 0x0000;
	}

	virtual u32 readLong(u8 PROCNUM, u32 addr)
	{
		return 0x00000000;
	}
};

ISlot2Interface* construct_Slot2_Arduino() { return new Slot2_Arduino(); }