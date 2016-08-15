#pragma once

#include "../common.hpp"
#include "../resources/database.hpp"

#include "../graphics/frame.hpp"
#include "../graphics/model.hpp"
#include "../graphics/camera.hpp"
#include "../graphics/postprocess.hpp"

namespace RedFox
{
	class RenderCommand
	{
		public:
			//TODO(?): Sposta il transform
			RenderCommand(u32 _technique, u32 _material, u32 _model, Transform* _transform);
			RenderCommand();

			//Permette di organizzare i comandi in modo da limitare gli switch nel contesto
			bool operator <(const RenderCommand& _other) const;

		public:
			u32 technique, material, model;
			Transform* transform;
	};

	class Renderer
	{
		public:
			Renderer();

			//Aggiunge un post process
			//TODO: Permetti di usare diversi stack di tecniche
			void pushPostProcess(PostProcess* _process);

			//Aggiunge un commando che verr� eseguito all'invocazione di flush
			void submitCommand(u32 _technique, u32 _material, u32 _model, Transform* _transform);
			void submitCommand(const RenderCommand& _command);

			//Sorta ed esegue tutti i comandi
			//TODO(?): Inoltra camera con questo metodo 
			void present(const Camera& _camera);

		private:
			vector<RenderCommand> m_commands;
			vector<unique<PostProcess>> m_postProcesses;
	};
}