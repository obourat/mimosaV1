#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>

class QStandardItemModel;

class Model : public QAbstractTableModel
{
public:
    // Constructeur
    explicit Model(const QStringList &attributesOfCurrentConfig, const QList<QMap<QString, QString> > &smallMapsFromMapName);
    // Destructeur
    ~Model();

    // Methodes de QAbstractTableModel a deriver

    // Compteur de lignes
    int rowCount(const QModelIndex &parent) const;
    //Compteur de colonnes
    int columnCount(const QModelIndex &parent) const;
    //Détemine les données présentes dans une case
    QVariant data(const QModelIndex &index, int role) const;
    //Détermine les données présentes dans le header
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
#if 0
    void sort(int column, Qt::SortOrder order);
#endif

private:
    //QList<QMap<QString, QString> > listOfMaps;
    QStandardItemModel *model;
};


#endif // MODEL_H