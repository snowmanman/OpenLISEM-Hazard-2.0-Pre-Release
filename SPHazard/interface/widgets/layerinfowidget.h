#ifndef LAYERINFOWIDGET_H
#define LAYERINFOWIDGET_H

#include "QWidget"
#include "QLineEdit"
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QGridLayout>
#include "QLabel"
#include "QDialog"
#include "QPushButton"
#include "QTableView"
#include "tablemodel.h"
#include "QMenuBar"
#include "QCoreApplication"
#include "iomanager.h"
#include "QLineEdit"
#include "tableplot.h"
#include "labeledwidget.h"
#include "scriptmanager.h"
#include "findreplacedialog.h"

class LayerInfoWidget : public QDialog
{
    Q_OBJECT;

    QWidget* m_MainWidget;
    QHBoxLayout * m_MainLayout;

    QIcon *icon_start;
    QIcon *icon_pause;
    QIcon *icon_stop;
    QIcon *icon_open;
    QIcon *icon_save;
    QIcon *icon_saveas;
    QIcon *icon_new;
    QIcon *icon_info;

    QIcon *icon_table_add;
    QIcon *icon_table_remove;
    QIcon *icon_table_size;
    QIcon *icon_table_addr;
    QIcon *icon_table_remover;
    QIcon *icon_table_title;
    QIcon *icon_table_datatype;
    QIcon *icon_table_sortasc;
    QIcon *icon_table_sortdesc;
    QIcon *icon_table_restoresort;
    QIcon *icon_table_search;

    QIcon *icon_zoomin;
    QIcon *icon_zoomout;
    QIcon *icon_plot;

    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveasAct;
    QAction *printAct;
    QAction *AddAct;
    QAction *RemoveAct;
    QAction *AddRAct;
    QAction *RemoveRAct;
    QAction *SetSizeAct;
    QAction *DatatypeAct;
    QAction *SearchAct;
    QAction *SortAAct;
    QAction *SortDAct;
    QAction *SortRAct;
    QAction *TitleAct;
    QAction *PlotAct;
    QToolButton *CalcAct;
    QAction *ZoomInAct;
    QAction *ZoomOutAct;
    QAction *InverseAct;

    QString m_Dir;
    QString m_Path_Current;

    MatrixTable * mt;
    TableModel *model;
    QSortFilterProxyModel * proxyModel;
    QTableView * m_Table;

    QHBoxLayout * m_SelectionInfoLayout;
    QLabel * m_SelectionInfoLabel;
    QLabel * m_SelectionTitleLabel;
    QLabel * m_SelectionDatatypeLabel;
    QLabel * m_UnsavedLabel;
    QLabel * m_FileLabel;

    QItemSelection m_PreviousSelection;
    QItemSelection m_CurrentSelection;

    QLineEdit * m_LineEdit;

    ScriptManager * m_ScriptManager;

    int srmin = 0;
    int srmax = 0;

    int scmin = 0;
    int scmax = 0;

    QList<int> m_SelectedColumnsList;
    QList<int> m_SelectedRowsList;

    bool m_HasChanges = false;

public:

    inline LayerInfoWidget(MatrixTable * tbl, bool can_edit = false, bool can_save = false, bool can_script = false, bool has_types_columns = false, bool has_type_horizontal = false, bool is_dialog = false, bool can_change_columns = true, bool can_change_rows = true) : QDialog()
    {



        m_ScriptManager = GetScriptManager();

        m_Dir = QCoreApplication::applicationDirPath();

        this->setMinimumSize(600,400);

        m_MainWidget = new QWidget();
        m_MainLayout = new QHBoxLayout();
        m_MainWidget->setLayout(m_MainLayout);


        QVBoxLayout * vl = new QVBoxLayout();
        this->setLayout(vl);



        QWidget * MenuWidgetExt = new QWidget();
        QHBoxLayout * mlExt = new QHBoxLayout(MenuWidgetExt);
        QWidget * MenuWidget = new QWidget();
        QHBoxLayout * ml = new QHBoxLayout(MenuWidget);
        MenuWidget->setLayout(ml);
        ml->setMargin(0);
        ml->setSpacing(0);
        mlExt->setMargin(0);
        mlExt->setSpacing(0);
        MenuWidgetExt->setLayout(mlExt);
        QMenuBar* mb = new QMenuBar();

        icon_start = new QIcon();
        icon_pause = new QIcon();
        icon_stop = new QIcon();
        icon_open = new QIcon();
        icon_save = new QIcon();
        icon_saveas = new QIcon();
        icon_new = new QIcon();
        icon_info = new QIcon();

        icon_start->addFile((m_Dir + SPH_FOLDER_ASSETS + "start1.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon_pause->addFile((m_Dir + SPH_FOLDER_ASSETS + "pause2.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon_stop->addFile((m_Dir + SPH_FOLDER_ASSETS + "stop1.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon_open->addFile((m_Dir + SPH_FOLDER_ASSETS + "fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon_save->addFile((m_Dir + SPH_FOLDER_ASSETS + "filesave.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon_saveas->addFile((m_Dir + SPH_FOLDER_ASSETS + "filesaveas.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon_new->addFile((m_Dir + SPH_FOLDER_ASSETS + "new.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon_info->addFile((m_Dir + SPH_FOLDER_ASSETS + "Info.png"), QSize(), QIcon::Normal, QIcon::Off);

        icon_table_add = new QIcon();
        icon_table_remove = new QIcon();
        icon_table_addr = new QIcon();
        icon_table_remover = new QIcon();
        icon_table_size = new QIcon();
        icon_table_title = new QIcon();
        icon_table_datatype = new QIcon();
        icon_table_sortasc = new QIcon();
        icon_table_sortdesc = new QIcon();
        icon_table_restoresort = new QIcon();
        icon_table_search = new QIcon();
        icon_plot = new QIcon();
        icon_zoomin = new QIcon();
        icon_zoomout = new QIcon();

        icon_table_add->addFile((m_Dir + SPH_FOLDER_ASSETS + "table_add.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon_table_remove->addFile((m_Dir + SPH_FOLDER_ASSETS + "table_remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon_table_addr->addFile((m_Dir + SPH_FOLDER_ASSETS + "table_addrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon_table_remover->addFile((m_Dir + SPH_FOLDER_ASSETS + "table_removerow.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon_table_size->addFile((m_Dir + SPH_FOLDER_ASSETS + "table_setsize.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon_table_title->addFile((m_Dir + SPH_FOLDER_ASSETS + "table_title.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon_table_datatype->addFile((m_Dir + SPH_FOLDER_ASSETS + "table_datatype.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon_table_sortasc->addFile((m_Dir + SPH_FOLDER_ASSETS + "table_sortasc.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon_table_sortdesc->addFile((m_Dir + SPH_FOLDER_ASSETS + "table_sortdesc.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon_table_restoresort->addFile((m_Dir + SPH_FOLDER_ASSETS + "table_restoresort.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon_table_search->addFile((m_Dir + SPH_FOLDER_ASSETS + "table_search.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon_plot->addFile((m_Dir + SPH_FOLDER_ASSETS + "plot.png"), QSize(), QIcon::Normal, QIcon::Off);

        icon_zoomin->addFile((m_Dir + SPH_FOLDER_ASSETS + "zoomin.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon_zoomout->addFile((m_Dir + SPH_FOLDER_ASSETS + "zoomout.png"), QSize(), QIcon::Normal, QIcon::Off);

        saveAct = new QAction(*icon_save,tr("&Save"), this);
        //saveAct->setShortcuts(QKeySequence::Save);
        saveAct->setToolTip(tr("Save the document to disk"));
        connect(saveAct, &QAction::triggered, this, &LayerInfoWidget::save);

        saveasAct = new QAction(*icon_saveas,tr("&Save As"), this);
        //saveasAct->setShortcuts(QKeySequence::SaveAs);
        saveasAct->setToolTip(tr("Save the document to disk"));
        connect(saveasAct, &QAction::triggered, this, &LayerInfoWidget::saveas);


        newAct = new QAction(*icon_new,tr("&New"), this);
        //saveAct->setShortcuts(QKeySequence::Save);
        newAct->setToolTip(tr("Create a new document"));
        connect(newAct, &QAction::triggered, this, &LayerInfoWidget::createnew);

        openAct = new QAction(*icon_open,tr("&Open"), this);
        //saveAct->setShortcuts(QKeySequence::Save);
        saveAct->setToolTip(tr("Open a document from file"));
        connect(openAct, &QAction::triggered, this, &LayerInfoWidget::opentable);

        printAct = new QAction(*icon_save,tr("&Print"), this);
        //saveAct->setShortcuts(QKeySequence::Save);
        printAct->setToolTip(tr("Print this document"));
        connect(printAct, &QAction::triggered, this, &LayerInfoWidget::print);

        AddAct = new QAction(*icon_table_add,tr("&Add"), this);
        //saveAct->setShortcuts(QKeySequence::Save);
        AddAct->setToolTip(tr("Add new column after current selection"));
        connect(AddAct, &QAction::triggered, this, &LayerInfoWidget::tableadd);

        RemoveAct = new QAction(*icon_table_remove,tr("&Remove"), this);
        //saveAct->setShortcuts(QKeySequence::Save);
        RemoveAct->setToolTip(tr("Remove the selected columns"));
        connect(RemoveAct, &QAction::triggered, this, &LayerInfoWidget::tableremove);

        AddRAct = new QAction(*icon_table_addr,tr("&Add"), this);
        //saveAct->setShortcuts(QKeySequence::Save);
        AddRAct->setToolTip(tr("Add new row after current selection"));
        connect(AddRAct, &QAction::triggered, this, &LayerInfoWidget::tableaddr);

        RemoveRAct = new QAction(*icon_table_remover,tr("&Remove"), this);
        //saveAct->setShortcuts(QKeySequence::Save);
        RemoveRAct->setToolTip(tr("Remove the selected rows"));
        connect(RemoveRAct, &QAction::triggered, this, &LayerInfoWidget::tableremover);

        SetSizeAct = new QAction(*icon_table_size,tr("&ReSize"), this);
        //saveAct->setShortcuts(QKeySequence::Save);
        SetSizeAct->setToolTip(tr("Resize the table"));
        connect(SetSizeAct, &QAction::triggered, this, &LayerInfoWidget::tableresize);

        SearchAct = new QAction(*icon_table_search,tr("&Search"), this);
        //saveAct->setShortcuts(QKeySequence::Save);
        SearchAct->setToolTip(tr("Search for entries containing a value"));
        connect(SearchAct, &QAction::triggered, this, &LayerInfoWidget::search);

        SortAAct = new QAction(*icon_table_sortasc,tr("&Sort Ascending"), this);
        //saveAct->setShortcuts(QKeySequence::Save);
        SortAAct->setToolTip(tr("Sort the table ascending based on selected column"));
        connect(SortAAct, &QAction::triggered, this, &LayerInfoWidget::sortasc);

        SortDAct = new QAction(*icon_table_sortdesc,tr("&Sort Descending"), this);
        //saveAct->setShortcuts(QKeySequence::Save);
        saveAct->setToolTip(tr("Save the document to disk"));
        connect(saveAct, &QAction::triggered, this, &LayerInfoWidget::sortdesc);

        SortRAct = new QAction(*icon_table_restoresort,tr("&Restore"), this);
        //saveAct->setShortcuts(QKeySequence::Save);
        SortRAct->setToolTip(tr("Undo any sorting"));
        connect(SortRAct, &QAction::triggered, this, &LayerInfoWidget::sortrestore);

        TitleAct = new QAction(*icon_table_title,tr("&Title"), this);
        //saveAct->setShortcuts(QKeySequence::Save);
        TitleAct->setToolTip(tr("Change Title of row/colum"));
        connect(TitleAct, &QAction::triggered, this, &LayerInfoWidget::changetitle);

        DatatypeAct = new QAction(*icon_table_datatype,tr("&Datatype"), this);
        //saveAct->setShortcuts(QKeySequence::Save);
        DatatypeAct->setToolTip(tr("Change the datatype of this row/column"));
        connect(DatatypeAct, &QAction::triggered, this, &LayerInfoWidget::changedatatype);

        PlotAct = new QAction(*icon_plot,tr("&Plot"), this);
        //saveAct->setShortcuts(QKeySequence::Save);
        PlotAct->setToolTip(tr("Plot the selected data"));
        connect(PlotAct, &QAction::triggered, this, &LayerInfoWidget::plot);

        CalcAct = new QToolButton();
        CalcAct->setText("Calculate");
        CalcAct->setIcon(*icon_start);
        //saveAct->setShortcuts(QKeySequence::Save);
        CalcAct->setToolTip(tr("Perform the entered calculation on this table"));
        connect(CalcAct, &QToolButton::pressed, this, &LayerInfoWidget::calculate);

        InverseAct = new QAction(*icon_start,tr("&Invert"), this);
        //saveAct->setShortcuts(QKeySequence::Save);
        InverseAct->setToolTip(tr("Invert the table"));
        connect(InverseAct, &QAction::triggered, this, &LayerInfoWidget::Invert);


        ZoomInAct = new QAction(*icon_zoomin,tr("&Zoom In"), this);
        //saveAct->setShortcuts(QKeySequence::Save);
        ZoomInAct->setToolTip(tr("Make the cells and contents larger"));
        connect(ZoomInAct, &QAction::triggered, this, &LayerInfoWidget::ZoomIn);


        ZoomOutAct = new QAction(*icon_zoomout,tr("&Zoom Out"), this);
        //saveAct->setShortcuts(QKeySequence::Save);
        ZoomOutAct->setToolTip(tr("Make the cells and contents smaller"));
        connect(ZoomOutAct, &QAction::triggered, this, &LayerInfoWidget::ZoomOut);



        mb->addSeparator();
        mb->addAction(newAct);
        mb->addAction(openAct);
        mb->addAction(saveAct);
        mb->addAction(saveasAct);
        mb->addAction(printAct);
        mb->addSeparator();
        mb->addAction(AddAct);
        mb->addAction(RemoveAct);
        mb->addAction(AddRAct);
        mb->addAction(RemoveRAct);
        mb->addSeparator();
        mb->addAction(SetSizeAct);
        mb->addSeparator();
        mb->addAction(SortAAct);
        mb->addAction(SortDAct);
        mb->addAction(SortRAct);
        mb->addSeparator();
        mb->addAction(TitleAct);
        mb->addAction(DatatypeAct);
        mb->addSeparator();
        mb->addAction(SearchAct);
        mb->addAction(PlotAct);
        mb->addAction(ZoomInAct);
        mb->addAction(ZoomOutAct);
        mb->addSeparator();

        m_MainLayout->setMenuBar(mb);

        mlExt->addWidget(MenuWidget);

        vl->addWidget(MenuWidgetExt);
        m_LineEdit = new QLineEdit();
        vl->addWidget(new QWidgetHDuo(m_LineEdit, CalcAct));
        vl->setMargin(1);



        mt = tbl;
        model = new TableModel(mt);
        m_Table = new QTableView();

        proxyModel = new QSortFilterProxyModel();
        proxyModel->setSourceModel( model );
        m_Table->setModel( proxyModel );

        //m_Table->setModel(model);
        m_MainLayout->addWidget(m_Table);
        vl->addWidget(m_MainWidget);

        m_Table->horizontalHeader()->setSectionsMovable(true);
        m_Table->verticalHeader()->setSectionsMovable(true);

        QHBoxLayout * m_SelectionInfoLayout = new QHBoxLayout();
        QWidget *  infowidget = new QWidget();
        infowidget->setLayout(m_SelectionInfoLayout);
        m_SelectionInfoLabel = new QLabel("Selection: ");
        m_SelectionTitleLabel = new QLabel("");
        m_SelectionDatatypeLabel = new QLabel("");
        m_UnsavedLabel = new QLabel("no changes");
        m_FileLabel = new QLabel("File: " + tbl->AS_FileName);

        m_SelectionInfoLayout->addWidget(m_SelectionInfoLabel);
        m_SelectionInfoLayout->addWidget(m_SelectionTitleLabel);
        m_SelectionInfoLayout->addWidget(m_SelectionDatatypeLabel);
        m_SelectionInfoLayout->addWidget(m_UnsavedLabel);
        m_SelectionInfoLayout->addWidget(m_FileLabel);

        vl->addWidget(infowidget);
        connect(m_Table->selectionModel(),&QItemSelectionModel::selectionChanged,this,&LayerInfoWidget::OnSelectionChanged);

        if(tbl->AS_FileName.isEmpty())
        {
            m_FileLabel->setText("File: " + tbl->AS_FileName);
        }else {

            m_FileLabel->setText("");
        }


        if(is_dialog)
        {
            QWidget * buttons = new QWidget();
            QHBoxLayout *buttonsl = new QHBoxLayout();
            buttons->setLayout(buttonsl);

            QPushButton * okb = new QPushButton("Ok");
            QPushButton * cancelb = new QPushButton("Cancel");

            connect(okb, SIGNAL(clicked(bool)),this,SLOT(onOkClicked()));
            connect(cancelb, SIGNAL(clicked(bool)),this,SLOT(onCancelClicked()));

            buttonsl->addWidget(okb);
            buttonsl->addWidget(cancelb);

            vl->addWidget(buttons);
        }

    }

    inline void AddRowCallBack()
    {

    }

    inline void AddColumnCallBack()
    {

    }

    inline MatrixTable * GetMatrixTable()
    {
        return model->getList()->Copy();
    }


    inline void SetCallBackRowChange()
    {

    }

    inline void SetCallBackColumnChange()
    {

    }

    inline void SetCallBackSelectionChanged()
    {


    }


public slots:

    inline void onOkClicked()
    {
        emit accept();
    }
    inline void onCancelClicked()
    {
        emit reject();
    }

    inline void createnew()
    {


    }

    inline void save()
    {

        //is it an existing file?
        QString savename;
        if(!(mt->AS_FileName.isEmpty()))
        {
            savename = mt->AS_FileName;
        }else {
            QString selectedFilter;
            QString path = QFileDialog::getSaveFileName(this,
                                                            QString("Give a table file name"),
                                                            QString("sph"),
                                                            QString("SPH Table Files (*.tbl);;All Files (*)"),
                                                            &selectedFilter);

            if(path.isEmpty())
            {
                return;
            }else
            {
                savename = path;
            }
        }

        //get save name

        model->getList()->SaveAs(savename,",");

        //save table

        m_FileLabel->setText("File: "+ mt->AS_FileName);
        m_HasChanges = false;
        m_UnsavedLabel->setText("Saved");

    }

    inline void saveas()
    {
        QFileInfo f(mt->AS_FileName);


        //get save name
        QString savename;
        QString selectedFilter;
        QString path = QFileDialog::getSaveFileName(this,
                                                        QString("Give a table file name"),
                                                        QString("sph"),
                                                        QString("SPH Table Files (*.tbl);;All Files (*)"),
                                                        &selectedFilter);

        if(path.isEmpty())
        {
            return;
        }else
        {
            savename = path;
        }

        //save table

        model->getList()->SaveAs(savename,",");

        m_FileLabel->setText("File: "+ mt->AS_FileName);
        m_HasChanges = false;
        m_UnsavedLabel->setText("Saved");

    }

    inline void opentable()
    {
        QFileInfo f(mt->AS_FileName);


        //get save name
        QString savename;
        QString path = QFileDialog::getOpenFileName(this,
                                            QString("Select Table File"),
                                            f.dir().path(),
                                            QString("*.tbl;*.csv;;*.*"));


    }


    inline void print()
    {


    }


    inline void sortasc()
    {
        std::sort(m_SelectedColumnsList.begin(),m_SelectedColumnsList.end());


        if(m_SelectedColumnsList.length() > 0)
        {
            //m_Table->setSortingEnabled(true);

            m_Table->sortByColumn(m_SelectedColumnsList.at(0), Qt::AscendingOrder);
        }else
        {
            QMessageBox msgBox;
            msgBox.setText("No columns selected.");
            msgBox.exec();
        }

    }

    inline void sortdesc()
    {
        std::sort(m_SelectedColumnsList.begin(),m_SelectedColumnsList.end());

        if(m_SelectedColumnsList.length() > 0)
        {
            //m_Table->setSortingEnabled(true);
            m_Table->sortByColumn(m_SelectedColumnsList.at(0), Qt::DescendingOrder);
        }else
        {
            QMessageBox msgBox;
            msgBox.setText("No columns selected.");
            msgBox.exec();
        }

    }

    inline void sortrestore()
    {
        std::sort(m_SelectedColumnsList.begin(),m_SelectedColumnsList.end());

        m_Table->sortByColumn(-1, Qt::AscendingOrder);

    }

    inline void calculate()
    {

        std::cout << "calculate " << std::endl;

        QString code = m_LineEdit->text();

        MatrixTable *t = model->getList()->Copy();

        SPHScript * s = m_ScriptManager->CompileScriptTable(code);


        asIScriptContext *ctx = m_ScriptManager->m_Engine->CreateContext();
        asIScriptFunction *func = s->scriptbuilder->GetModule()->GetFunctionByDecl("Table TableEdit(Table &t)");
        ctx->Prepare(func);

        ctx->SetArgObject(0,t);

        try
        {

            int r = ctx->Execute();

            if( r == asEXECUTION_FINISHED )
            {

                MatrixTable *ret = (MatrixTable*) ctx->GetReturnObject();
                model->SetAllData(ret);
                m_Table->update();

                std::cout << "calc finished " << std::endl;

            }else
            {
                QMessageBox::critical(this, "SPHazard",
                   QString("Error during table calculation. \n Code:\n " + code));
            }
        }catch(...)
        {
            SPH_ERROR("Exception thrown during script run");

        }

        ctx->Release();

        OnDataChanged();
    }
    inline void plot()
    {

        TablePlotter * plotter = new TablePlotter(model->getList()->Copy());

        plotter->show();
    }
    inline void search()
    {

        FindReplaceDialog * m_FindReplaceDialog = new FindReplaceDialog(this);
        m_FindReplaceDialog->setModal(false);
        m_FindReplaceDialog->setTableEdit(m_Table);
        m_FindReplaceDialog->show();

    }
    inline void tableadd()
    {
        //add empty column
        MatrixTable *t = model->getList();
        if(t->GetNumberOfCols() == 0 && t->GetNumberOfRows() == 0)
        {
            t->SetSize(1,1);

        }else
        {
            t->AddColumn(scmax+1);
        }
        model->SetAllData(t);
        m_Table->update();

        OnDataChanged();

    }
    inline void tableremove()
    {

        std::sort(m_SelectedColumnsList.begin(),m_SelectedColumnsList.end());

        if(m_SelectedColumnsList.size() > 0)
        {
            MatrixTable *t = model->getList();

            for(int i = m_SelectedColumnsList.size() - 1; i > -1; i--)
            {
                t->RemoveColumn(m_SelectedColumnsList.at(i));
            }
            model->SetAllData(t);
            m_Table->update();

        }else
        {
            QMessageBox msgBox;
            msgBox.setText("No columns selected.");
            msgBox.exec();
        }
        OnDataChanged();

    }

    inline void tableaddr()
    {
        //add empty column
        MatrixTable *t = model->getList();
        if(t->GetNumberOfCols() == 0 && t->GetNumberOfRows() == 0)
        {
            t->SetSize(1,1);

        }else
        {
            t->AddRow(srmax+1);
        }
        model->SetAllData(t);
        m_Table->update();
        OnDataChanged();
    }
    inline void tableremover()
    {
        std::sort(m_SelectedRowsList.begin(),m_SelectedRowsList.end());

        if(m_SelectedRowsList.size() > 0)
        {
            MatrixTable *t = model->getList();

            for(int i = m_SelectedRowsList.size() - 1; i > -1; i--)
            {
                t->RemoveRow(m_SelectedColumnsList.at(i));
            }
            model->SetAllData(t);
            m_Table->update();

        }else
        {
            QMessageBox msgBox;
            msgBox.setText("No rows selected.");
            msgBox.exec();
        }

        OnDataChanged();

    }

    inline void tableresize()
    {


    }

    inline void changetitle()
    {


    }

    inline void changedatatype()
    {

    }


    inline void deletecolumns()
    {

    }

    inline void deleterows()
    {


    }

    inline void addcolumn()
    {

    }

    inline void addrow()
    {

    }


    inline void ZoomIn()
    {

    }

    inline void ZoomOut()
    {


    }

    inline void Invert()
    {


    }

    inline void OnSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
    {



        //we want to know this when another function is called
        m_PreviousSelection = deselected;
        m_CurrentSelection = selected;

        QModelIndexList indices = m_Table->selectionModel()->selectedIndexes();

        m_SelectedColumnsList.clear();
        m_SelectedRowsList.clear();

        QSet<int> rows;
        QSet<int> columns;

        if(indices.size() > 0)
        {

            for(int i = 0; i < indices.length(); i++)
            {
                if(i == 0)
                {
                    srmin = indices.at(i).row();
                    srmax = indices.at(i).row();
                    scmin = indices.at(i).column();
                    scmax = indices.at(i).column();
                }else
                {
                    srmin = std::min(srmin,indices.at(i).row());
                    srmax = std::max(srmax,indices.at(i).row());
                    scmin = std::min(scmin,indices.at(i).column());
                    scmax = std::max(scmax,indices.at(i).column());
                }

                if(!rows.contains(indices.at(i).row()))
                {
                    rows.insert(indices.at(i).row());
                }
                if(!columns.contains(indices.at(i).column()))
                {
                    columns.insert(indices.at(i).column());
                }
            }
        }else
        {
            srmin = 0;
            srmax = 0;
            scmin = 0;
            scmax = 0;
        }

        m_SelectedColumnsList = m_SelectedColumnsList.fromSet(columns);
        m_SelectedRowsList = m_SelectedRowsList.fromSet(rows);    }


    inline void OnDataChanged()
    {
        m_HasChanges = true;
        m_UnsavedLabel->setText("Unsaved changes");

    }

};


#endif // LAYERINFOWIDGET_H
