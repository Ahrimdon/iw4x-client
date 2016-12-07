#include "STDInclude.hpp"

namespace Components
{
	Utils::Memory::Allocator Command::MemAllocator;
	std::map<std::string, wink::slot<Command::Callback>> Command::FunctionMap;
	std::map<std::string, wink::slot<Command::Callback>> Command::FunctionMapSV;

	std::string Command::Params::join(size_t startIndex)
	{
		std::string result;

		for (size_t i = startIndex; i < this->length(); ++i)
		{
			if (i > startIndex) result.append(" ");
			result.append(this->operator[](i));
		}

		return result;
	}

	char* Command::Params::operator[](size_t index)
	{
		return this->get(index);
	}

	char* Command::ClientParams::get(size_t index)
	{
		if (index >= this->length()) return "";
		return Game::cmd_argv[this->commandId][index];
	}

	size_t Command::ClientParams::length()
	{
		return Game::cmd_argc[this->commandId];
	}

	char* Command::ServerParams::get(size_t index)
	{
		if (index >= this->length()) return "";
		return Game::cmd_argv_sv[this->commandId][index];
	}

	size_t Command::ServerParams::length()
	{
		return Game::cmd_argc_sv[this->commandId];
	}

	void Command::Add(const char* name, Command::Callback* callback)
	{
		std::string command = Utils::String::ToLower(name);

		if (Command::FunctionMap.find(command) == Command::FunctionMap.end())
		{
			Command::AddRaw(name, Command::MainCallback);
		}

		Command::FunctionMap[command] = callback;
	}

	void Command::AddSV(const char* name, Command::Callback* callback)
	{
		if (Loader::IsPregame())
		{
			MessageBoxA(0, "Registering server commands in pregamestate is illegal!", 0, MB_ICONERROR);

#ifdef DEBUG
			__debugbreak();
#endif

			return;
		}

		std::string command = Utils::String::ToLower(name);

		if (Command::FunctionMapSV.find(command) == Command::FunctionMapSV.end())
		{
			Command::AddRawSV(name, Command::MainCallbackSV);

			// If the main command is registered as Cbuf_AddServerText, the command will be redirected to the SV handler
			Command::AddRaw(name, Game::Cbuf_AddServerText);
		}

		Command::FunctionMapSV[command] = callback;
	}

	void Command::AddRaw(const char* name, void(*callback)(), bool key)
	{
		Game::Cmd_AddCommand(name, callback, Command::Allocate(), key);
	}

	void Command::AddRawSV(const char* name, void(*callback)())
	{
		Game::Cmd_AddServerCommand(name, callback, Command::Allocate());

		// If the main command is registered as Cbuf_AddServerText, the command will be redirected to the SV handler
		Command::AddRaw(name, Game::Cbuf_AddServerText);
	}

	void Command::Execute(std::string command, bool sync)
	{
		command.append("\n"); // Make sure it's terminated

		if (sync)
		{
			Game::Cmd_ExecuteSingleCommand(0, 0, command.data());
		}
		else
		{
			Game::Cbuf_AddText(0, command.data());
		}
	}

	Game::cmd_function_t* Command::Find(std::string command)
	{
		Game::cmd_function_t* cmdFunction = *Game::cmd_functions;

		while (cmdFunction)
		{
			if (cmdFunction->name && cmdFunction->name == command)
			{
				return cmdFunction;
			}

			cmdFunction = cmdFunction->next;
		}

		return nullptr;
	}

	Game::cmd_function_t* Command::Allocate()
	{
		return Command::MemAllocator.allocate<Game::cmd_function_t>();
	}

	void Command::MainCallback()
	{
		Command::ClientParams params(*Game::cmd_id);

		std::string command = Utils::String::ToLower(params[0]);

		if (Command::FunctionMap.find(command) != Command::FunctionMap.end())
		{
			Command::FunctionMap[command](&params);
		}
	}

	void Command::MainCallbackSV()
	{
		Command::ServerParams params(*Game::cmd_id_sv);

		std::string command = Utils::String::ToLower(params[0]);

		if (Command::FunctionMapSV.find(command) != Command::FunctionMapSV.end())
		{
			Command::FunctionMapSV[command](&params);
		}
	}

	Command::Command()
	{
		AssertSize(Game::cmd_function_t, 24);

		// Disable native noclip command
		Utils::Hook::Nop(0x474846, 5);

		Command::Add("noclip", [] (Command::Params*)
		{
			int clientNum = Game::CG_GetClientNum();
			if (!Game::CL_IsCgameInitialized() || clientNum >= 18 || clientNum < 0 || !Game::g_entities[clientNum].client)
			{
				Logger::Print("You are not hosting a match!\n");
				Toast::Show("cardicon_stop", "Error", "You are not hosting a match!", 3000);
				return;
			}

			if (!Dvar::Var("sv_cheats").get<bool>())
			{
				Logger::Print("Cheats disabled!\n");
				Toast::Show("cardicon_stop", "Error", "Cheats disabled!", 3000);
				return;
			}

			Game::g_entities[clientNum].client->flags ^= Game::PLAYER_FLAG_NOCLIP;

			Logger::Print("Noclip toggled\n");
			Toast::Show("cardicon_abduction", "Success", "Noclip toggled", 3000);
		});

		Command::Add("ufo", [] (Command::Params*)
		{
			int clientNum = Game::CG_GetClientNum();
			if (!Game::CL_IsCgameInitialized() || clientNum >= 18 || clientNum < 0 || !Game::g_entities[clientNum].client)
			{
				Logger::Print("You are not hosting a match!\n");
				Toast::Show("cardicon_stop", "Error", "You are not hosting a match!", 3000);
				return;
			}

			if (!Dvar::Var("sv_cheats").get<bool>())
			{
				Logger::Print("Cheats disabled!\n");
				Toast::Show("cardicon_stop", "Error", "Cheats disabled!", 3000);
				return;
			}

			Game::g_entities[clientNum].client->flags ^= Game::PLAYER_FLAG_UFO;

			Logger::Print("UFO toggled\n");
			Toast::Show("cardicon_abduction", "Success", "UFO toggled", 3000);
		});

		Command::Add("setviewpos", [](Command::Params* params)
		{
			int clientNum = Game::CG_GetClientNum();
			if (!Game::CL_IsCgameInitialized() || clientNum >= 18 || clientNum < 0 || !Game::g_entities[clientNum].client)
			{
				Logger::Print("You are not hosting a match!\n");
				Toast::Show("cardicon_stop", "Error", "You are not hosting a match!", 3000);
				return;
			}

			if (!Dvar::Var("sv_cheats").get<bool>())
			{
				Logger::Print("Cheats disabled!\n");
				Toast::Show("cardicon_stop", "Error", "Cheats disabled!", 3000);
				return;
			}

			if (params->length() != 4 && params->length() != 6)
			{
				Logger::Print("Invalid coordinate specified!\n");
				Toast::Show("cardicon_stop", "Error", "Invalid coordinate specified!", 3000);
				return;
			}

			float pos[3] = { 0.0f, 0.0f, 0.0f };
			float orientation[3] = { 0.0f, 0.0f, 0.0f };
			
			pos[0] = strtof(params->get(1), NULL);
			pos[1] = strtof(params->get(2), NULL);
			pos[2] = strtof(params->get(3), NULL);
			
			if(params->length() == 6)
			{
				orientation[0] = strtof(params->get(4), NULL);
				orientation[1] = strtof(params->get(5), NULL);
			}

			Game::TeleportPlayer(&Game::g_entities[clientNum], pos, orientation);

			// Logging that will spam the console and screen if people use cinematics
			//Logger::Print("Successfully teleported player!\n");
			//Toast::Show("cardicon_abduction", "Success", "You have been teleported!", 3000);
		});
	}

	Command::~Command()
	{
		Command::MemAllocator.clear();
		Command::FunctionMap.clear();
		Command::FunctionMapSV.clear();
	}
}
