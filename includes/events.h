#ifndef EVENTS_H
#define EVENTS_H
using namespace std;

class EventArgs {
public:
	virtual ~EventArgs() {}
};

class StringEventArgs : public EventArgs {
	string payload_;
public:
	explicit StringEventArgs(const string& payload) : payload_(payload) {}
	const string& Payload() const { return payload_; }
};

class Event {
	class Callback {
		void* pSender_;
		const EventArgs& args_;

	public:
		Callback(void* pSender, const EventArgs& args) : pSender_(pSender), args_(args) {}
		void operator()(pair<long, function<void(void*, const EventArgs&)>> p) const {
			p.second(pSender_, args_);
		}
	};
	map<long, function<void(void*, const EventArgs&)>> callbacks_;
	long token_ = 0;

public:
	void operator()(void* pSender, const EventArgs& args) const {
		for_each(callbacks_.begin(), callbacks_.end(), Callback(pSender, args));
	}
	long Subscribe(function<void(void*, const EventArgs&)> f) {
		token_++;
    callbacks_.insert(make_pair(token_, f));
		return token_;
	}
	void Unsubscribe(long token) {
		callbacks_.erase(token);
	}
};
#endif