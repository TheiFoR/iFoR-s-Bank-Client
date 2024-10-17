import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

StackLayout{
    currentIndex: core.userRegistrationStep
    //currentIndex: 1

    NewAccount{}
    LinkingToTelegram{}
}
