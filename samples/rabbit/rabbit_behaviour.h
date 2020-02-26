#ifndef RABBIT_BEHAVIOUR_H_
#define RABBIT_BEHAVIOUR_H_

#include "rabbit_profile.h"
#include "rabbit_context.h"

#include "controllers/denoise_component.h"
#include "controllers/file_component.h"
#include "controllers/entities_component.h"
#include "controllers/canvas_component.h"
#include "controllers/offline_component.h"
#include "controllers/player_component.h"
#include "controllers/h264_component.h"
#include "controllers/ui_component.h"
#include "controllers/mark_component.h"
#include "controllers/client_component.h"

namespace rabbit
{
	class RabbitBehaviour final : public octoon::GameComponent
	{
		OctoonDeclareSubClass(RabbitBehaviour, octoon::GameComponent)
	public:
		RabbitBehaviour() noexcept;
		RabbitBehaviour(const std::shared_ptr<RabbitProfile>& profile) noexcept;
		~RabbitBehaviour() noexcept;

		const std::shared_ptr<RabbitProfile>& getProfile() const noexcept;

		void open(const std::string& filepath) noexcept(false);
		void close() noexcept;
		bool isOpen() const noexcept;

		void openModel() noexcept;
		void saveModel() noexcept;

		bool startRecord(const std::string& path) noexcept;
		void stopRecord() noexcept;

		void loadHDRi(const std::string& path) noexcept;
		void clearHDRi() noexcept;

		void renderPicture(const std::string& path) noexcept(false);

		void addComponent(IRabbitComponent* component) noexcept;
		void removeComponent(const IRabbitComponent* component) noexcept;
		const std::vector<IRabbitComponent*>& getComponents() const noexcept;
		void enableComponents() noexcept;
		void disableComponents() noexcept;

		IRabbitComponent* getComponent(const std::type_info& type) const noexcept;
		template<typename T>
		T* getComponent() const noexcept { return dynamic_cast<T*>(this->getComponent(typeid(T))); }

		void sendMessage(const std::string& event, const std::any& data = nullptr) noexcept;
		void addMessageListener(const std::string& event, std::function<void(const std::any&)> listener) noexcept;
		void removeMessageListener(const std::string& event, std::function<void(const std::any&)> listener) noexcept;

		virtual octoon::GameComponentPtr clone() const noexcept override;

	private:
		void onActivate() noexcept override;
		void onDeactivate() noexcept override;

		void onFixedUpdate() noexcept override;
		void onUpdate() noexcept override;
		void onLateUpdate() noexcept override;

	private:
		std::shared_ptr<RabbitProfile> profile_;
		std::shared_ptr<RabbitContext> context_;

		std::unique_ptr<FileComponent> fileComponent_;
		std::unique_ptr<CanvasComponent> canvasComponent_;
		std::unique_ptr<EntitiesComponent> entitiesComponent_;
		std::unique_ptr<OfflineComponent> offlineComponent_;
		std::unique_ptr<PlayerComponent> playerComponent_;
		std::unique_ptr<DenoiseComponent> denoiseComponent_;
		std::unique_ptr<H264Component> h264Component_;
		std::unique_ptr<UIComponent> uiComponent_;
		std::unique_ptr<MarkComponent> markComponent_;
		std::unique_ptr<ClientComponent> clientComponent_;

		std::vector<IRabbitComponent*> components_;
		std::unordered_map<std::string, octoon::runtime::signal<void(const std::any&)>> dispatchEvents_;
	};
}

#endif