#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QString>
#include <QMap>
#include <QSettings>

class DataManager;

class FileWriter
{
public:
    FileWriter(DataManager *dataManager);
    ~FileWriter();

    //Modifie dans le fichier XML les éléments de mapChangeList en le comparant avec la map associée et en le modifiant en conséquences
    void modifyFiles(const QString mapName);
    //Ajoute au fichier XML les éléments de mapAddList à la fin de celui-ci, en prenant en compte les attribus de balise et le numéro de clé
    void addToFiles(const QString mapName);
    //Supprime du fichier XML les éléments renseignés dans mapEraseList
    void eraseOfFiles(const QString mapName);
    //Compare les mapAddList et mapEraseList pour supprimer les clés présentes dans les deux (optimisation en cas d'annulation d'ajout)
    void compareCurrentMaps(const QString mapName);

private:
    //Définition des objets nécessaire pour la gestion des données
    DataManager *dataManager;

    //Définition des maps d'objets a gérer dans les différentes fonctions
    QMap<QString, QString> mapChangeList;
    QMap<QString, QString> mapAddList;
    QMap<QString, QString> mapEraseList;
    //Settings récupéré de dataManager permettant de connaître le chemin des fichiers
    QSettings *settings;
};

#endif // FILEWRITER_H
