#!/usr/bin/env python

# high level:
# QTreeView is connected to QStandardItemModel which is a tree of QStandardItem nodes

# more detailed:
# the tree view is connected to the model with .setModel()
# the items become children of one another via .appendRow()
# the root item is retrieved with .invisibleRootItem()

# two ways to set header data
# model.setData(model.index(0, self.FROM), mailFrom)

# from https://learndataanalysis.org/display-hierarchical-data-with-qtreeview-widget-pyqt5-tutorial/
# good tutorial: https://felgo.com/doc/qt/model-view-programming/

import sys

from PyQt5.Qt import QStandardItemModel, QStandardItem
from PyQt5.QtGui import QFont, QColor
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QApplication, QMainWindow, QTreeView


def breakpoint():
    '''Set a tracepoint in the Python debugger that works with Qt'''
    from pdb import set_trace
    from PyQt5.QtCore import pyqtRemoveInputHook
    pyqtRemoveInputHook()
    set_trace()

class StandardItem(QStandardItem):
    def __init__(self, txt='', font_size=12, set_bold=False, color=QColor(0, 0, 0), col_A="Header_FOO", col_B="Header_BAR", col_C="Header_BAZ"):
        super().__init__()

        fnt = QFont('Monaco', font_size)
        fnt.setBold(set_bold)

        self.setEditable(False)
        self.setForeground(color)
        self.setFont(fnt)
        self.setText(txt)

        #self.setData(0, col_A)
        #self.setData(1, col_B)
        #self.setData(2, col_C)

class AppDemo(QMainWindow):
    HEADER_A_IDX, HEADER_B_IDX, HEADER_C_IDX = range(3)

    def __init__(self):
        super().__init__()
        self.setWindowTitle('World Country Diagram')
        self.resize(500, 700)

        # 
        treeView = QTreeView()
        #treeView.setHeaderHidden(True)
        treeView.setRootIsDecorated(True)
        treeView.setAlternatingRowColors(True)

        # create model
        treeModel = QStandardItemModel(0, 3) # rows, columns
        treeModel.setHeaderData(self.HEADER_A_IDX, Qt.Horizontal, "Header A")
        treeModel.setHeaderData(self.HEADER_B_IDX, Qt.Horizontal, "Header B")
        treeModel.setHeaderData(self.HEADER_C_IDX, Qt.Horizontal, "Header C")

        # America
        america = StandardItem('America', 16, set_bold=True)

        california = StandardItem('California', 14)
        america.appendRow(california)

        oakland = StandardItem('Oakland', 12, color=QColor(155, 0, 0))
        sanfrancisco = StandardItem('San Francisco', 12, color=QColor(155, 0, 0))
        sanjose = StandardItem('San Jose', 12, color=QColor(155, 0, 0))

        california.appendRow([oakland, QStandardItem('AAA'), QStandardItem('BBB')])
        california.appendRow(sanfrancisco)
        california.appendRow([sanjose, None, QStandardItem('YYY')])

        texas = StandardItem('Texas', 14)
        america.appendRow(texas)

        austin = StandardItem('Austin', 12, color=QColor(155, 0, 0))
        houston = StandardItem('Houston', 12, color=QColor(155, 0, 0))
        dallas = StandardItem('dallas', 12, color=QColor(155, 0, 0))

        texas.appendRow(austin)
        texas.appendRow(houston)
        texas.appendRow(dallas)

        # Canada 
        canada = StandardItem('Canada', 16, set_bold=True)
        alberta = StandardItem('Alberta', 14)
        bc = StandardItem('British Columbia', 14)
        ontario = StandardItem('Ontario', 14)
        canada.appendRows([alberta, bc, ontario])

        rootNode = treeModel.invisibleRootItem()
        rootNode.appendRow(america)
        rootNode.appendRow(canada)

        treeView.setModel(treeModel)
        treeView.expandAll()
        treeView.doubleClicked.connect(self.showClick)

        self.setCentralWidget(treeView)

    # idx: PyQt5.QtCore.QModelIndex
    def showClick(self, idx):
        #breakpoint()

        stack = []
        while True:
            stack.append(idx)
            if idx == idx.parent():
                break
            idx = idx.parent()
        
        indent = ''
        while stack:
            idx = stack.pop()
            print(f'{indent} -> ({idx.row()},{idx.column()}) data:{idx.data()}')
            indent += '  '
            
app = QApplication(sys.argv)        

demo = AppDemo()
demo.show()

sys.exit(app.exec_())
