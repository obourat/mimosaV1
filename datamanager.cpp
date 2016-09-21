#include "datamanager.h"

#include <QStringBuilder>

//Constructeur
DataManager::DataManager()
{
}

//Destructeur
DataManager::~DataManager()
{

}

void DataManager::insertDataToMap(const QString &mapName, const QString &key, const QMap<QString, QString> &map)
{
    // Si la clef est vide
    if(key.isEmpty())
    {
        // Quitter
        return;
    }

    // Choix de la map par rapport au nom donné
    if(mapName == "mapGCA")
    {
        // Si la map ne contient pas deja la clef key
        if(!mapGCA.contains(mapName))
        {
            // Insertion des données
            mapGCA.insert(key, map);
        }
    }
    // Choix de la map par rapport au nom donné
    else if(mapName == "mapGAT")
    {
        // Si la map ne contient pas deja la clef key
        if(!mapGAT.contains(mapName))
        {
            // Insertion des données
            mapGAT.insert(key, map);
        }
    }
    // Choix de la map par rapport au nom donné
    else if(mapName == "mapGVE")
    {
        // Si la map ne contient pas deja la clef key
        if(!mapGVE.contains(mapName))
        {
            // Insertion des données
            mapGVE.insert(key, map);
        }
    }
    // Choix de la map par rapport au nom donné
    else if(mapName == "mapGCS")
    {
        // Si la map ne contient pas deja la clef key
        if(!mapGCS.contains(mapName))
        {
            // Insertion des données
            mapGCS.insert(key, map);
        }
    }
    // Choix de la map par rapport au nom donné
    else if(mapName == "mapGRS")
    {
        // Si la map ne contient pas deja la clef key
        if(!mapGRS.contains(mapName))
        {
            // Insertion des données
            mapGRS.insert(key, map);
        }
    }

}


const QMap<QString, QMap<QString, QString> >* DataManager::getMapFromName(const QString &mapName) const
{
    //Retourne la map correspondante sur le bon nom est rentré
    if(mapName == "mapGCA")
    {
        return &mapGCA;
    }
    //Retourne la map correspondante sur le bon nom est rentré
    else if(mapName == "mapGAT")
    {
        return &mapGAT;
    }
    //Retourne la map correspondante sur le bon nom est rentré
    else if(mapName == "mapGVE")
    {
        return &mapGVE;
    }
    //Retourne la map correspondante sur le bon nom est rentré
    else if(mapName == "mapGCS")
    {
        return &mapGCS;
    }
    //Retourne la map correspondante sur le bon nom est rentré
    else if(mapName == "mapGRS")
    {
        return &mapGRS;
    }
    //Si un nom invalide ou nul est rentré, on ne renvoie rien
    else
    {
        return NULL;
    }
}
QString DataManager::getCurrentConfigName() const
{
    return currentConfigName;
}

void DataManager::setCurrentConfigName(const QString &value)
{
    currentConfigName = value;
}


const QStringList DataManager::getAttributesOfCurrentConfig(const QString &objectType)
{
    //On définit une liste de clés keys nous permettant de lister les clés des confs de l'objet objectType
    QStringList keys;

    //On définit un iterateur sur la grande qMap pour passer en revue les clés
    QMap<QString, QMap<QString, QString> >::Iterator iterator;

    //Pour toutes les clés de la qMap GCA
    for (iterator = mapGCA.begin(); iterator != mapGCA.end(); ++iterator)
    {
        //Si l'élément CodeObjet de la clé sélectionnée par l'iterateur est égal au type d'objet rentré
        if(iterator.value()["CodeObjet"] == objectType)
        {
            //On ajoute la clé sélectionnée par l'itérateur dans la liste keys
            keys.append(iterator.key());
        }
    }
    //On définit un string currentKey qui sert a sélectionner la clé pour la configuration courante
    QString currentConfigKey;
    //Pour toutes les clés de la liste keys des clés sélectionnées
    for (int i = 0; i <  keys.length(); ++i)
    {
#warning probleme signe euro
        //Si la balise NomConf de la clé sélectionnée contient le mot standard
        int compareValue = QString ::compare(mapGCA[keys[i]]["NomConf"], currentConfigName, Qt::CaseSensitive);
        if (compareValue == 0)
        {
            //on sélectionne cette clé comme configuration courante
            currentConfigKey = keys[i];
            //exit
            break;
        }
    }

    //On efface la liste de clés
    keys.clear();
    //Pour chaque clé de la mapGAT
    for (iterator = mapGAT.begin(); iterator != mapGAT.end(); ++iterator)
    {
        //Si la valeur de la balise InCnfAtt est égale à la valeur de la clé de la configuration courante
        if(iterator.value()["IdCnfAtt"] == currentConfigKey)
        {
            //On ajoute la clé sélectionnée par l'iterateur dans la liste keys
            keys.append(iterator.key());
        }
    }
    //On renvoie la liste de clés (correspondant à la liste des clés des attributs pour la configuration d'attribut courante)
    return keys;
}

const QList<QMap<QString, QString> > DataManager::getSmallMapsFromMapName(const QString &mapName, QString codeObject)
{
    //On définit une liste de maps<clé, valeur>
    QList<QMap<QString, QString> > maps;
    //On définit une map selectedMap qui sera égale à la map sélectionnée
    const QMap<QString, QMap<QString, QString> >* selectedMap;
    //retourne la map correspondante au nom rentré par l'utilisateur (si ce nom est valide)
    selectedMap = getMapFromName(mapName);

    //Si la map est nulle
    if(selectedMap == NULL)
    {
        //On retourne une liste vide
        return maps;
    }
    //On définit un iterateur qui parcours les clés de la map sélectionnée
    QMap<QString, QMap<QString, QString> >::ConstIterator iterator;
    //Tant que l'iterateur n'a pas parcouru toutes les clés de la map sélectionnée
    for (iterator= selectedMap->begin(); iterator != selectedMap->end(); ++iterator)
    {
        //On ajoute dans la liste maps les valeurs correpsondantes au contenu de la clé (la sous map)
        maps << selectedMap->value(iterator.key());
    }
    //On sélectionne dans maps les attributs que l'on veut afficher et on retourne le résultat
    return selectAttributesOfSmallMapsList(maps, codeObject);



}


const QList<QMap<QString, QString> > DataManager::selectAttributesOfSmallMapsList(const QList<QMap<QString, QString> > maps, const QString codeObject)
{
    QList<QMap<QString, QString> > mapsSelectedForCurrentConfig;
    QStringList attributesOfCurrentConfig = getAttributesOfCurrentConfig(codeObject);
    QMap<QString, QString > mapTempOfSelectedAttributes;
    QMap<QString, QString> valueOfSmallMapSelected;
    QString iteratorAttribute;
    QString nomAttributeDisplayed;
    QString nomAttributeSelected;
    QString valueAttributeSelected;
    QString numeroInterne;
    QString infoInterne;
    QString keyOfmapConcordance;


    //Tant que l'on a pas parcouru tous les éléments de maps
    for (int j=0; j < maps.length(); ++j)
    {
        mapTempOfSelectedAttributes.clear();
        //Tant que l'on a pas parcouru l'ensemble des clés des attributs sélectionnés pour la conf
        for(int i=0 ; i<attributesOfCurrentConfig.length(); ++i)
        {
            //IteratorAttribute prend en paramètre la clé de l'attribut sur lequel il itère
            iteratorAttribute = attributesOfCurrentConfig.at(i);

            //Si l'indicateur d'affichage de l'attribut séléctionné est égal à "oui"
            if(mapGAT[iteratorAttribute]["IndicAffichage"] == "Oui")
            {
                //On sélectionne le Titre de l'attribut à afficher dans l'en tête
                nomAttributeDisplayed = mapGAT[iteratorAttribute]["NomAttribut"];
                //On selectionne le premier critère NuméroInterne permettant de trouver le nom de la balise à sélectionner
                numeroInterne = mapGAT[iteratorAttribute]["NumeroInterne"];
                //On sélectionne le deuxième critère InfoInterne permettant de trouver le nom de la balise à sélectionner
                infoInterne = mapGAT[iteratorAttribute]["InfoInterne"];

                //On obtient la clé de la valeur à aller chercher dans mapConcordance pour obtenir le nom de la balise sur le XML en concaténant les 3 critères
                keyOfmapConcordance = codeObject % numeroInterne % infoInterne;

                //On cherche la valeur dans mapConcordance
                nomAttributeSelected = mapConcordance[keyOfmapConcordance];
                //On sélectionne le l'élément à traiter dans la petite map
                valueOfSmallMapSelected = maps.at(j);
                //On va chercher la valeur dans l'élément de la petite map à la balise nomAttributeSelected
                valueAttributeSelected = valueOfSmallMapSelected[nomAttributeSelected];
                //On insère la valeur dans la map temporaire des éléments sélectionnés
                mapTempOfSelectedAttributes.insert(nomAttributeDisplayed, valueAttributeSelected);

            }

        }
        //On stocke dans la nouvelle map tous les attributs de la configuration courante
        mapsSelectedForCurrentConfig << mapTempOfSelectedAttributes;
    }

    return mapsSelectedForCurrentConfig;
}

void DataManager::setDataOfMapConcordance()
{
    QString nameConfXML;
    QString idConf;
    QString codeObject;
    QString numeroInterne;
    QString infoInterne;
    QString titre;
    QString currentKey;
    QString newKey;
    //On définit un iterateur sur les grande qMap pour passer en revue les clés
    QMap<QString, QMap<QString, QString> >::Iterator iteratorGCS;
    QMap<QString, QMap<QString, QString> >::Iterator iteratorGCA;
    QMap<QString, QMap<QString, QString> >::Iterator iteratorGAT;

    //Pour chaque éléments de mapGCS
    for(iteratorGCS = mapGCS.begin(); iteratorGCS != mapGCS.end(); ++iteratorGCS)
    {
        //On stocke la clé = au codeObjet
        currentKey = iteratorGCS.key();
        //On prend en paramètre le nom de la conf servant à l'export XML
        nameConfXML = iteratorGCS.value()["NomConfXML"];

        //Pour chaque configuration d'attribut
        for(iteratorGCA = mapGCA.begin(); iteratorGCA != mapGCA.end(); ++iteratorGCA)
        {
            //Si le code objet correspond
            if(iteratorGCA.value()["CodeObjet"] == currentKey)
            {
                //Si il s'agit de la bonne configuration pour le bon code objet
                if(iteratorGCA.value()["NomConf"] == nameConfXML)
                {
                    //On stocke l'Id de la configuration
                    idConf = iteratorGCA.value()["Id"];
                    //Pour chaque attribut de la map d'attribut
                    for(iteratorGAT = mapGAT.begin(); iteratorGAT != mapGAT.end(); ++iteratorGAT)
                    {
                        //Si l'attribut correpond à la bonne configuration
                        if(iteratorGAT.value()["IdCnfAtt"] == idConf)
                        {
                            //On stocke les valeurs des triplés qui une fois concaténés vont nous servir de clés pour accéder au nom de balise
                            codeObject = iteratorGAT.value()["CodeObj"];
                            numeroInterne = iteratorGAT.value()["NumeroInterne"];
                            infoInterne = iteratorGAT.value()["InfoInterne"];
                            titre = iteratorGAT.value()["Titre"];

                            newKey = codeObject % numeroInterne % infoInterne;

                            //On insère la valeur dans mapConcordance
                            mapConcordance.insert(newKey, titre);
                        }
                    }
                }
            }
        }


    }
}
