#include <quickfix/Application.h>
#include <quickfix/MessageCracker.h>
#include <quickfix/SessionSettings.h>
#include <quickfix/FileStore.h>
#include <quickfix/FileLog.h>
#include <quickfix/SocketAcceptor.h>

#include <iostream>

class AcceptorApp final : public FIX::Application, public FIX::MessageCracker {
public:
    void onCreate(const FIX::SessionID& sid) override {
        std::cout << "CREATE: " << sid.toString() << "\n";
    }

    void onLogon(const FIX::SessionID& sid) override {
        std::cout << "LOGON:  " << sid.toString() << "\n";
    }

    void onLogout(const FIX::SessionID& sid) override {
        std::cout << "LOGOUT: " << sid.toString() << "\n";
    }

    void toAdmin(FIX::Message&, const FIX::SessionID&) override {}
    void toApp(FIX::Message&, const FIX::SessionID&) override {}

    void fromAdmin(const FIX::Message& msg, const FIX::SessionID& sid) override {
        std::cout << "ADMIN IN (" << sid.toString() << "): " << msg.toString() << "\n";
    }

    void fromApp(const FIX::Message& msg, const FIX::SessionID& sid) override {
        std::cout << "APP IN   (" << sid.toString() << "): " << msg.toString() << "\n";
    }
};

int main(int argc, char** argv) {
    const char* cfg_path = (argc > 1) ? argv[1] : "acceptor/cfg/acceptor_equities_4.2.cfg";

    try {
        FIX::SessionSettings settings(cfg_path);
        AcceptorApp app;
        FIX::FileStoreFactory store_factory(settings);
        FIX::FileLogFactory log_factory(settings);
        FIX::SocketAcceptor acceptor(app, store_factory, settings, log_factory);

        acceptor.start();
        std::cout << "Acceptor started using: " << cfg_path << "\n";
        std::cout << "Press Enter to stop.\n";
        std::cin.get();
        acceptor.stop();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << "\n";
        return 1;
    }
}
