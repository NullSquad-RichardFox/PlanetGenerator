#pragma once


#define BIND_FUNCTION(func) [this](auto&&... args) -> decltype(auto) { return this->func(std::forward<decltype(args)>(args)...); }
#define FUNC_CONCAT(...) __VA_ARGS__

#define DECLARE_EVENT_DELEGATE_Impl(delegateName, eventName, callback, compTypes, compParams, compArgs, comma, retParams, retArgs) \
	class D##delegateName##Handle \
	{\
	private:\
		struct delegateName\
		{\
			std::tuple<compTypes> Comparison;\
			std::function<callback> Callback;\
			void* BoundObj = nullptr;\
		};\
		\
	public:\
		D##delegateName##Handle()\
			:m_Events({}) {}\
		\
		inline FUUID BindEvent(compParams comma void* BindObj, std::function<callback> Callback)\
		{\
			FUUID uuid;\
			m_Events[uuid] = delegateName(std::make_tuple(compArgs), Callback, BindObj);\
			EVENT_LOG("New listener bound to event {0}, current size {1}.", eventName, m_Events.size());\
			return uuid;\
		}\
		\
		inline void CancelEvent(FUUID uuid)\
		{\
			m_Events.erase(uuid);\
		}\
		\
		inline void Broadcast(compParams retParams)\
		{\
			EVENT_LOG("Event {0} broadcasted to {1} listeners.", eventName, m_Events.size());\
			for (const auto& [uuid, event] : m_Events)\
			{\
				if (event.BoundObj == nullptr)\
				{\
					LOG_WARN("event skipped");\
					m_Events.erase(uuid);\
					continue;\
				}\
				\
				if (!event.Comparison._Equals(std::make_tuple(compArgs))) continue;\
				\
				event.Callback(retArgs);\
				EVENT_LOG("Event {0} called.", eventName);\
			}\
		}\
		inline const std::unordered_map<FUUID, delegateName>& GetBoundEvents() const { return m_Events; }\
		\
	private:\
		std::unordered_map<FUUID, delegateName> m_Events;\
		std::string m_Name = eventName;\
	};


#define DECLARE_EVENT_DELEGATE(eventDelegate) DECLARE_EVENT_DELEGATE_Impl(eventDelegate, #eventDelegate, void(), FUNC_CONCAT(int), FUNC_CONCAT(), FUNC_CONCAT(0), FUNC_CONCAT(), FUNC_CONCAT(), FUNC_CONCAT())

#define DECLARE_EVENT_DELEGATE_OneRet(eventDelegate, ret1Type) DECLARE_EVENT_DELEGATE_Impl(eventDelegate, #eventDelegate, void(ret1Type), FUNC_CONCAT(int), FUNC_CONCAT(), FUNC_CONCAT(0), FUNC_CONCAT(), FUNC_CONCAT(ret1Type ret1), FUNC_CONCAT(ret1))
#define DECLARE_EVENT_DELEGATE_TwoRets(eventDelegate, ret1Type, ret2Type) DECLARE_EVENT_DELEGATE_Impl(eventDelegate, #eventDelegate, void(ret1Type, ret2Type), FUNC_CONCAT(int), FUNC_CONCAT(), FUNC_CONCAT(0), FUNC_CONCAT(), FUNC_CONCAT(ret1Type ret1, ret2Type ret2), FUNC_CONCAT(ret1, ret2))
#define DECLARE_EVENT_DELEGATE_ThreeRets(eventDelegate, ret1Type, ret2Type, ret3Type) DECLARE_EVENT_DELEGATE_Impl(eventDelegate, #eventDelegate, void(ret1Type, ret2Type, ret3Type), FUNC_CONCAT(int), FUNC_CONCAT(), FUNC_CONCAT(0), FUNC_CONCAT(), FUNC_CONCAT(ret1Type ret1, ret2Type ret2, ret3Type ret3), FUNC_CONCAT(ret1, ret2, ret3))
#define DECLARE_EVENT_DELEGATE_FourRets(eventDelegate, ret1Type, ret2Type, ret3Type, ret4Type) DECLARE_EVENT_DELEGATE_Impl(eventDelegate, #eventDelegate, void(ret1Type, ret2Type, ret3Type, ret4Type), FUNC_CONCAT(int), FUNC_CONCAT(), FUNC_CONCAT(0), FUNC_CONCAT(), FUNC_CONCAT(ret1Type ret1, ret2Type ret2, ret3Type ret3, ret4Type ret4), FUNC_CONCAT(ret1, ret2, ret3, ret4))
#define DECLARE_EVENT_DELEGATE_FiveRets(eventDelegate, ret1Type, ret2Type, ret3Type, ret4Type, ret5Type) DECLARE_EVENT_DELEGATE_Impl(eventDelegate, #eventDelegate, void(ret1Type, ret2Type, ret3Type, ret4Type, ret5Type), FUNC_CONCAT(int), FUNC_CONCAT(), FUNC_CONCAT(0), FUNC_CONCAT(), FUNC_CONCAT(ret1Type ret1, ret2Type ret2, ret3Type ret3, ret4Type ret4, ret5Type ret5), FUNC_CONCAT(ret1, ret2, ret3, ret4, ret5))
#define DECLARE_EVENT_DELEGATE_SixRets(eventDelegate, ret1Type, ret2Type, ret3Type, ret4Type, ret5Type, ret6Type) DECLARE_EVENT_DELEGATE_Impl(eventDelegate, #eventDelegate, void(ret1Type, ret2Type, ret3Type, ret4Type, ret5Type, ret6Type), FUNC_CONCAT(int), FUNC_CONCAT(), FUNC_CONCAT(0), FUNC_CONCAT(), FUNC_CONCAT(ret1Type ret1, ret2Type ret2, ret3Type ret3, ret4Type ret4, ret5Type ret5, ret6Type ret6), FUNC_CONCAT(ret1, ret2, ret3, ret4, ret5, ret6))

#define DECLARE_EVENT_DELEGATE_OneParam(eventDelegate, param1Type) DECLARE_EVENT_DELEGATE_Impl(eventDelegate, #eventDelegate, void(), FUNC_CONCAT(param1Type), FUNC_CONCAT(param1Type param1), FUNC_CONCAT(param1), FUNC_CONCAT(,), FUNC_CONCAT(), FUNC_CONCAT())
#define DECLARE_EVENT_DELEGATE_TwoParams(eventDelegate, param1Type, param2Type) DECLARE_EVENT_DELEGATE_Impl(eventDelegate, #eventDelegate, void(), FUNC_CONCAT(param1Type, param2Type), FUNC_CONCAT(param1Type param1, param2Type param2), FUNC_CONCAT(param1, param2), FUNC_CONCAT(,), FUNC_CONCAT(), FUNC_CONCAT())
#define DECLARE_EVENT_DELEGATE_ThreeParams(eventDelegate, param1Type, param2Type, param3Type) DECLARE_EVENT_DELEGATE_Impl(eventDelegate, #eventDelegate, void(), FUNC_CONCAT(param1Type, param2Type, param3Type), FUNC_CONCAT(param1Type param1, param2Type param2, param3Type param3), FUNC_CONCAT(param1, param2, param3), FUNC_CONCAT(,), FUNC_CONCAT(), FUNC_CONCAT())
#define DECLARE_EVENT_DELEGATE_FourParams(eventDelegate, param1Type, param2Type, param3Type, param4Type) DECLARE_EVENT_DELEGATE_Impl(eventDelegate, #eventDelegate, void(), FUNC_CONCAT(param1Type, param2Type, param3Type, param4Type), FUNC_CONCAT(param1Type param1, param2Type param2, param3Type param3, param4Type param4), FUNC_CONCAT(param1, param2, param3, param4), FUNC_CONCAT(,), FUNC_CONCAT(), FUNC_CONCAT())
#define DECLARE_EVENT_DELEGATE_FiveParams(eventDelegate, param1Type, param2Type, param3Type, param4Type, param5Type) DECLARE_EVENT_DELEGATE_Impl(eventDelegate, #eventDelegate, void(), FUNC_CONCAT(param1Type, param2Type, param3Type, param4Type, param5Type), FUNC_CONCAT(param1Type param1, param2Type param2, param3Type param3, param4Type param4, param5Type param5), FUNC_CONCAT(param1, param2, param3, param4, param5), FUNC_CONCAT(,), FUNC_CONCAT(), FUNC_CONCAT())
#define DECLARE_EVENT_DELEGATE_SixParams(eventDelegate, param1Type, param2Type, param3Type, param4Type, param5Type, param6Type) DECLARE_EVENT_DELEGATE_Impl(eventDelegate, #eventDelegate, void(), FUNC_CONCAT(param1Type, param2Type, param3Type, param4Type, param5Type, param6Type), FUNC_CONCAT(param1Type param1, param2Type param2, param3Type param3, param4Type param4, param5Type param5, param6Type param6), FUNC_CONCAT(param1, param2, param3, param4, param5, param6), FUNC_CONCAT(,), FUNC_CONCAT(), FUNC_CONCAT())
